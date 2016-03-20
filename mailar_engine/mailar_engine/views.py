import base64
import json

import datetime

from django.contrib.auth.models import User

from mailar_engine.models import Message, Mail, AccessList
from mailar_engine.serializers import MailSerializer, MessageSerializer

from rest_framework import status
from rest_framework.authentication import TokenAuthentication, BasicAuthentication
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.authtoken.models import Token


@api_view(['GET'])
@authentication_classes((TokenAuthentication, BasicAuthentication))
@permission_classes((IsAuthenticated,))
def example_view(request):
    content = {
        'user': unicode(request.user),  # `django.contrib.auth.User` instance.
        'auth': unicode(request.auth),  # None
    }
    return Response(content)


@api_view(['POST'])
@authentication_classes((BasicAuthentication, ))
@permission_classes((IsAuthenticated,))
def login_view(request):
    content = {
        'token': unicode(Token.objects.get(user=request.user))
    }
    return Response(content)


@api_view(['POST'])
def register(request):
    try:
        decoded_data = base64.b64decode(request.POST[''])
        user = decoded_data.split(':')[0]
        password = decoded_data.split(':')[1]
    except KeyError, IndexError:
        return Response(data={'detail': 'Auth data not passed or invalid. Valid: base64(user:password)'},
                        status=status.HTTP_400_BAD_REQUEST)

    user, created = User.objects.get_or_create(username=user)
    if not created:
        return Response(data={'detail': 'User %s already exists' % user}, status=status.HTTP_409_CONFLICT)

    user.set_password(password)
    user.save()

    token = Token.objects.create(user=user)

    return Response(data={'detail': 'Created user: %s' % user,
                          'token': token.key}, status=status.HTTP_201_CREATED)


@api_view(['POST', 'GET'])
@authentication_classes((TokenAuthentication, ))
@permission_classes((IsAuthenticated,))
def message(request, mid):
    if request.method == 'GET':
        if mid == 'incoming':
            data = Mail.objects.filter(to_user=request.user)
            print 'here'
        elif mid == 'outgoing':
            data = Mail.objects.filter(from_user=request.user)
        else:
            try:
                msg = Message.objects.get(id=int(mid))
                try:
                    AccessList.objects.get(item=msg,
                                           clearance=request.user)
                except AccessList.DoesNotExist:
                    return Response(data={'detail': 'Access denied'},
                                    status=status.HTTP_403_FORBIDDEN)

                m = Mail.objects.get(message=msg)
                m.is_new = False
                m.save()
                return Response(MessageSerializer(msg).data)
            except Message.DoesNotExist:
                data = {'detail': 'No such message'}
                return Response(data=data, status=status.HTTP_404_NOT_FOUND)
        if len(data):
            return Response(MailSerializer(data, many=True).data)
        else:
            data = {'detail': 'No messages for you'}
            return Response(data=data, status=status.HTTP_204_NO_CONTENT)
    elif request.method == 'POST':
        try:
            parsed_body = json.loads(request.body.decode('utf-8'))
        except Exception as e:
            data = {'detail': '%s' % e}
            return Response(data=data, status=status.HTTP_500_INTERNAL_SERVER_ERROR)
        try:
            subject = parsed_body['subject']
            text = parsed_body['text']
            date = datetime.datetime.now()
            to_users = []
            if 'to' in parsed_body.keys() and len(parsed_body['to']):
                if type(parsed_body) is str:
                    to_users = [parsed_body['to']]
                else:
                    for u in parsed_body['to']:
                        try:
                            to_users.append(User.objects.get(username=u))
                        except User.DoesNotExist:
                            raise Exception('User %s does not exist' % u)
        except Exception as e:
            data = {'detail': '%s' % e}
            return Response(data=data, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

        msg = Message.objects.create(subject=subject,
                                     text=text,
                                     date=date)
        msg.save()
        AccessList.objects.create(item=msg, clearance=request.user).save()
        for u in to_users:
            Mail.objects.create(from_user=request.user,
                                to_user=u,
                                message=msg,
                                is_new=True).save()
            AccessList.objects.create(item=msg, clearance=u).save()
        return Response(data={'id': msg.id},
                        status=status.HTTP_201_CREATED)
