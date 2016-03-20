import base64

from django.contrib.auth.models import User

from rest_framework import status
from rest_framework.authentication import TokenAuthentication, BasicAuthentication
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response
from rest_framework.decorators import api_view, authentication_classes, permission_classes
from rest_framework.authtoken.models import Token


@api_view(['GET'])
@authentication_classes((TokenAuthentication, BasicAuthentication))
@permission_classes((IsAuthenticated,))
def example_view(request, format=None):
    content = {
        'user': unicode(request.user),  # `django.contrib.auth.User` instance.
        'auth': unicode(request.auth),  # None
    }
    return Response(content)


@api_view(['POST'])
def register(request):
    try:
        decoded_data = base64.b64decode(request.POST[''])
        user = decoded_data.split(':')[0]
        password = decoded_data.split(':')[1]
    except KeyError, IndexError:
        return Response(data={'error': 'Auth data not passed or invalid. Valid: base64(user:password)'},
                        status=status.HTTP_400_BAD_REQUEST)

    user, created = User.objects.get_or_create(username=user)
    if not created:
        return Response(data={'error': 'User %s already exists' % user}, status=status.HTTP_409_CONFLICT)

    user.set_password(password)
    user.save()

    token = Token.objects.create(user=user)

    return Response(data={'info': 'Created user: %s' % user,
                          'token': token.key}, status=status.HTTP_201_CREATED)