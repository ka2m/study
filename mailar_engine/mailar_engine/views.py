import base64
import json
import datetime


from django.db.models import Q

# models are imported in serializers
from mailar_engine.serializers import *

from rest_framework import status
from rest_framework.authentication import TokenAuthentication, BasicAuthentication
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.authtoken.models import Token


# Fail-safe decorators

def message_exists(func):
    def protected(request, message_id, *args, **kwargs):
        try:
            Message.objects.get(id=int(message_id))
            return func(request, message_id, *args, **kwargs)
        except Message.DoesNotExist:
            return {'detail': 'No such message'}, status.HTTP_404_NOT_FOUND
    return protected


def box_exists(func):
    def protected(request, message_id, *args, **kwargs):
        ml = Box.objects.filter(owner=request.user,
                                mail__message_id__exact=int(message_id))
        if not len(ml):
            return {'detail': 'No such message in your inbox'}, status.HTTP_404_NOT_FOUND
        return func(request, message_id, *args, **kwargs)

    return protected


def acl(func):
    def protected(request, message_id, *args, **kwargs):
        m = Mail.objects.filter(Q(message=int(message_id),
                                  from_user=request.user) |
                                Q(message=int(message_id),
                                  to_user=request.user,
                                  is_draft=False))
        if len(m):
            return func(request, message_id, *args, **kwargs)
        else:
            return {'detail': 'Access denied'}, status.HTTP_403_FORBIDDEN
    return protected


# Register/login/logout

@api_view(['POST'])
def register(request):
    try:
        decoded_data = base64.b64decode(json.loads(request.body.decode('utf-8'))['auth'])
        user = decoded_data.split(':')[0]
        password = decoded_data.split(':')[1]
    except Exception:
        return Response(data={'detail': 'Auth data not passed or invalid. Valid: base64(user:password)'},
                        status=status.HTTP_400_BAD_REQUEST)

    user, created = User.objects.get_or_create(username=user)
    if not created:
        return Response(data={'detail': 'User %s already exists' % user}, status=status.HTTP_409_CONFLICT)

    user.set_password(password)
    user.save()

    token = Token.objects.create(user=user)

    return Response(data={'token': token.key}, status=status.HTTP_201_CREATED)


@api_view(['POST'])
@authentication_classes((BasicAuthentication, ))
@permission_classes((IsAuthenticated,))
def login_view(request):
    content = {
        'token': unicode(Token.objects.get_or_create(user=request.user)[0])
    }
    return Response(content)


@api_view(['POST'])
@authentication_classes((BasicAuthentication, ))
@permission_classes((IsAuthenticated,))
def logout(request):
    pass


# Message-related

@api_view(['POST'])
@authentication_classes((TokenAuthentication, ))
@permission_classes((IsAuthenticated,))
def create_message(request):
    try:
        rb = json.loads(request.body.decode('utf-8'))
        subject = 'No subject' if 'subject' not in rb.keys() else rb['subject']
        text = '' if 'text' not in rb.keys() else rb['text']

        to_users = []
        if 'to' in rb.keys() and len(rb['to']):
            if type(rb['to']) is str or type(rb['to']) is unicode:
                rb['to'] = [rb['to']]
            for u in rb['to']:
                try:
                    to_users.append(User.objects.get(username=u))
                except User.DoesNotExist:
                    data = {'detail': 'User %s does not exist' % u}
                    return Response(data=data,
                                    status=status.HTTP_400_BAD_REQUEST)
        else:
            to_users = [None]
        to_users = list(set(to_users))
        m = Message.objects.create(subject=subject,
                                   text=text)
        m.save()

        for u in to_users:
            ml = Mail.objects.create(from_user=request.user,
                                     to_user=u,
                                     message=m)
            ml.save()

            Box.objects.create(owner=request.user,
                               mail=ml,
                               is_new=False).save()

        return Response(MessageIdOnlySerializer(m).data,
                        status=status.HTTP_201_CREATED)
    except Exception as e:
        data = {'detail': '%s' % str(e)}
        return Response(data=data, status=status.HTTP_500_INTERNAL_SERVER_ERROR)


@api_view(['GET', 'POST', 'PUT', 'UPDATE', 'DELETE'])
@authentication_classes((TokenAuthentication, ))
@permission_classes((IsAuthenticated,))
def message(request, message_id):
    if request.method == 'GET':
        data, s = api_message_get(request, message_id)
        return Response(data=MessageSerializer(data).data, status=s) \
            if s == status.HTTP_200_OK else Response(data=data, status=s)
    if request.method == 'POST':
        try:
            action = json.loads(request.body.decode('utf-8'))['action']
            if action == 'mark_as_read':
                data, s = api_message_mark_as_read(request, message_id)
                return Response(data=data, status=s)
            if action == 'send':
                data, s = api_message_send(request, message_id)
                return Response(data=data, status=s)
            raise Exception('Action not in (mark_as_read, send)')
        except KeyError:
            data = {'detail': 'No action passed'}
            return Response(data=data, status=status.HTTP_400_BAD_REQUEST)
        except Exception as e:
            data = {'detail': str(e)}
            return Response(data=data, status=status.HTTP_400_BAD_REQUEST)
    if request.method == 'PUT':
        data, s = api_message_update(request, message_id)
        return Response(data=data, status=s)
    if request.method == 'DELETE':
        data, s = api_message_delete(request, message_id)
        return Response(data=data, status=s)


@message_exists
@acl
def api_message_get(request, message_id):
    try:
        m = Message.objects.get(id=int(message_id))
        return m, status.HTTP_200_OK
    except Exception as e:
        return {'detail': str(e)}, status.HTTP_500_INTERNAL_SERVER_ERROR


@message_exists
@box_exists
@acl
def api_message_mark_as_read(request, message_id):
    try:
        # filter for case send to yourself
        mb = Box.objects.filter(mail__message_id__exact=int(message_id),
                                mail__to_user=request.user,
                                owner=request.user)
        for m in mb:
            m.is_new = False
            m.save()
        return {'detail': 'Message %s read' % message_id}, status.HTTP_200_OK
    except Exception as e:
        return {'detail': str(e)}, status.HTTP_500_INTERNAL_SERVER_ERROR


@message_exists
@acl
def api_message_send(request, message_id):
    if message_id is None:
        data = {'detail': 'No message id provided'}
        return data, status.HTTP_400_BAD_REQUEST

    m = Message.objects.get(id=int(message_id))
    m.date = datetime.datetime.now()
    m.save()
    recipients = Mail.objects.filter(message=m)
    if not len(recipients) or None in recipients:
        data = {'detail': 'No recipients'}
        return data, status.HTTP_400_BAD_REQUEST

    for r in recipients:
        r.is_draft = False
        r.save()
        ml = Mail.objects.get(message=m, to_user=r.to_user)
        Box.objects.create(owner=r.to_user, mail=ml).save()
    data = {'detail': 'Message %d sent' % int(message_id)}
    return data, status.HTTP_200_OK


@message_exists
@acl
def api_message_delete(request, message_id):
    if message_id is None:
        data = {'detail': 'No message id provided'}
        return data, status.HTTP_400_BAD_REQUEST

    try:
        m = Message.objects.get(id=int(message_id))

        Box.objects.filter(owner=request.user,
                           mail__message=m).delete()
        if len(Mail.objects.filter(message=m, is_draft=True)):
            Mail.objects.filter(message=m, is_draft=True).delete()
            if not len(Mail.objects.filter(message=m, is_draft=False)):
                Message.objects.filter(id=int(message_id)).delete()

        data = {'detail': 'Message %d deleted' % int(message_id)}
        return data, status.HTTP_200_OK
    except Exception as e:
        data = {'detail': str(e)}
        return data, status.HTTP_500_INTERNAL_SERVER_ERROR


@message_exists
@acl
def api_message_update(request, message_id):
    if message_id is None:
        data = {'detail': 'No message id provided'}
        return data, status.HTTP_400_BAD_REQUEST
    try:
        m = Message.objects.get(id=int(message_id))

        if len(Mail.objects.filter(message=m, is_draft=False)):
            data = {'detail': 'Message already sent'}
            return data, status.HTTP_400_BAD_REQUEST

        rb = json.loads(request.body.decode('utf-8'))
        m.subject = m.subject if 'subject' not in rb.keys() else rb['subject']
        m.text = text = m.text if 'text' not in rb.keys() else rb['text']
        m.date = datetime.datetime.now()
        m.save()

        Box.objects.filter(mail__message=m).delete()
        Mail.objects.filter(message=m).delete()

        if 'to' in rb.keys() and len(rb['to']):
            if type(rb['to']) is str or type(rb['to']) is unicode:
                rb['to'] = [rb['to']]
            for u in list(set(rb['to'])):
                try:
                    _u = User.objects.get(username=u)
                    ml, _ = Mail.objects.get_or_create(from_user=request.user,
                                                       to_user=_u,
                                                       message=m)
                    ml.save()
                    Box.objects.create(owner=request.user,
                                       mail=ml,
                                       is_new=False).save()
                except User.DoesNotExist:
                    data = {'detail': 'User %s does not exist' % u}
                    return data, status.HTTP_400_BAD_REQUEST

        data = {'detail': 'Message %d updated' % int(message_id)}
        return data, status.HTTP_200_OK

    except Exception as e:
        data = {'detail': str(e)}
        return data, status.HTTP_500_INTERNAL_SERVER_ERROR


@api_view(['GET'])
@authentication_classes((TokenAuthentication, ))
@permission_classes((IsAuthenticated,))
def box(request):
    """ Get messages for user basing on parameter ?filter
       allowed types:
       in - incoming messages
       out - outgoing messages
       drafts - outgoing drafts
       if none passed, all will be showed
    """
    try:
        filter_type = request.GET['filter']
        if filter_type == 'in':
            return Response(BoxSerializer(Box.objects.filter(owner=request.user,
                                                             mail__to_user=request.user,
                                                             mail__is_draft=False,
                                                             ),
                                          many=True).data)
        if filter_type == 'out':
            return Response(BoxSerializer(Box.objects.filter(owner=request.user,
                                                             mail__from_user=request.user,
                                                             mail__is_draft=False),
                                          many=True).data)
        if filter_type == 'draft':
            return Response(BoxSerializer(Box.objects.filter(owner=request.user,
                                                             mail__from_user=request.user,
                                                             mail__is_draft=True),
                                          many=True).data)
        data = {'detail': 'Filtering not supported. Supported ones: in, out, draft'}
        return Response(data=data, status=status.HTTP_400_BAD_REQUEST)
    except KeyError:
        return Response(BoxSerializer(Box.objects.filter(Q(owner=request.user,
                                                           mail__from_user=request.user) |
                                                         Q(owner=request.user,
                                                           mail__to_user=request.user,
                                                           mail__is_draft=False)),
                                      many=True).data)
