from django.db import models
from django.contrib.auth.models import User


class Message(models.Model):
    subject = models.CharField(max_length=100)
    content = models.TextField
    date = models.DateTimeField(auto_now=True)


class Mail(models.Model):
    from_user = models.ForeignKey(User, related_name='sender_user')
    to_user = models.ForeignKey(User, related_name='receiver_user')
    message = models.ForeignKey('Message')
