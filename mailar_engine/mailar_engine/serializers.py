from mailar_engine.models import *
from rest_framework import serializers
from django.contrib.auth.models import User


class UserPublicSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ('username', )


class MessageSerializer(serializers.ModelSerializer):
    class Meta:
        model = Message
        fields = ('date', 'subject', 'text')


class MailSerializer(serializers.ModelSerializer):
    from_user = UserPublicSerializer()
    to_user = UserPublicSerializer()

    class Meta:
        model = Mail
        fields = ('from_user', 'to_user', 'message', 'is_new')