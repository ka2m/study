from django.db import models
from django.contrib.auth.models import User


class AccessList(models.Model):
    item = models.ForeignKey('Message')
    clearance = models.ForeignKey(User)


class Mail(models.Model):
    from_user = models.ForeignKey(User, related_name='sender_user')
    to_user = models.ForeignKey(User, related_name='receiver_user')
    message = models.ForeignKey('Message')
    is_new = models.BooleanField(default=True)

    class Meta:
        ordering = ['message', 'is_new']


class Message(models.Model):
    subject = models.CharField(max_length=100)
    text = models.CharField(max_length=5000, null=True, blank=True)
    date = models.DateTimeField(auto_now=True)

    class Meta:
        ordering = ['date', 'subject']

