from django.db import models
from django.contrib.auth.models import User


class Box(models.Model):
    owner = models.ForeignKey(User)
    mail = models.ForeignKey('Mail')
    is_new = models.BooleanField(default=True)

    class Meta:
        ordering = ['-is_new', 'mail']


class Mail(models.Model):
    from_user = models.ForeignKey(User, related_name='sender_user')
    to_user = models.ForeignKey(User, related_name='receiver_user', null=True, blank=True)
    message = models.ForeignKey('Message')
    is_draft = models.BooleanField(default=True)

    class Meta:
        ordering = ['is_draft', 'message']


class Message(models.Model):
    subject = models.CharField(max_length=100)
    text = models.CharField(max_length=5000, default='')
    date = models.DateTimeField(auto_now=True)

    class Meta:
        ordering = ['-date', '-subject']

