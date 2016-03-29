from rest_framework import status
from rest_framework.test import APITestCase, APIClient
from rest_framework.authtoken.models import Token
from django.contrib.auth.models import User
from mailar_engine.models import Mail, Message, Box
import json
import base64


class RegisterTest(APITestCase):
    def test_register(self):
        user = 'testuser'
        password = 'testpassword'
        encoded = base64.b64encode('%s:%s' % (user, password))

        data = {'auth': encoded}
        response = self.client.post('/api/register', data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(json.loads(response.content).keys(), ['token'])
        self.assertEqual(User.objects.get(username='testuser').username, 'testuser')

    def test_register_repeat(self):
        user = 'testuser'
        password = 'testpassword'
        encoded = base64.b64encode('%s:%s' % (user, password))

        data = {'auth': encoded}
        self.client.post('/api/register', data, format='json')
        response = self.client.post('/api/register', data, format='json')
        self.assertEqual(response.status_code, status.HTTP_409_CONFLICT)
        self.assertEqual(json.loads(response.content)['detail'], 'User testuser already exists')
        self.assertEqual(User.objects.filter(username='testuser').count(), 1)

    def test_register_nodata(self):
        response = self.client.post('/api/register')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        r = 'Auth data not passed or invalid. Valid: base64(user:password)'
        self.assertEqual(json.loads(response.content)['detail'], r)
        self.assertEqual(User.objects.filter(username='testuser').count(), 0)


class LoginTest(APITestCase):
    token = ''
    encoded = ''

    def setUp(self):
        user = 'testuser'
        password = 'testpassword'
        self.encoded = base64.b64encode('%s:%s' % (user, password))

        data = {'auth': self.encoded}
        r = self.client.post('/api/register', data, format='json')
        self.token = json.loads(r.content)['token']

    def test_login(self):
        client = APIClient()
        client.credentials(HTTP_AUTHORIZATION='Basic ' + self.encoded)

        r = client.post('/api/login')
        self.assertEqual(r.status_code, status.HTTP_200_OK)
        self.assertEqual(json.loads(r.content)['token'], self.token)

    def test_login_fail(self):
        client = APIClient()
        client.credentials(HTTP_AUTHORIZATION='Basic somewronghash')

        r = client.post('/api/login')
        self.assertEqual(r.status_code, status.HTTP_401_UNAUTHORIZED)


class CreateMessageTest(APITestCase):
    def setUp(self):
        self.u, _ = User.objects.get_or_create(username='testuser', password='secret')
        t, _ = Token.objects.get_or_create(user=self.u)
        self.client = APIClient()
        self.client.credentials(HTTP_AUTHORIZATION='Token ' + t.key)
        User.objects.get_or_create(username='seconduser', password='secret')
        User.objects.get_or_create(username='thirduser', password='secret')


    def test_simple_create(self):
        data = {'subject': 'Hello',
                'to': 'testuser',
                'text': 'Hi there'
                }
        r = self.client.post('/api/message', data, format='json')
        self.assertEqual(r.status_code, status.HTTP_201_CREATED)
        mid = json.loads(r.content)['id']
        self.assertEqual(len(Mail.objects.filter(from_user=self.u,
                                                 to_user=self.u,
                                                 message_id=mid)), 1)
        self.assertEqual(len(Message.objects.filter(subject='Hello',
                                                    text='Hi there')), 1)

        self.assertEqual(len(Box.objects.filter(owner=self.u,
                                                mail__message_id=mid)), 1)

    def test_create_empty_subject(self):
        data = {'to': 'testuser',
                'text': 'Hi there'
                }
        r = self.client.post('/api/message', data, format='json')
        self.assertEqual(r.status_code, status.HTTP_201_CREATED)
        mid = json.loads(r.content)['id']
        self.assertEqual(len(Mail.objects.filter(from_user=self.u,
                                                 to_user=self.u,
                                                 message_id=mid)), 1)
        self.assertEqual(len(Message.objects.filter(subject='No subject',
                                                    text='Hi there')), 1)

        self.assertEqual(len(Box.objects.filter(owner=self.u,
                                                mail__message_id=mid)), 1)

    def test_create_empty_to(self):
        data = {'to': '',
                'text': 'Hi there'
                }
        r = self.client.post('/api/message', data, format='json')
        self.assertEqual(r.status_code, status.HTTP_201_CREATED)
        mid = json.loads(r.content)['id']
        self.assertEqual(len(Mail.objects.filter(from_user=self.u,
                                                 to_user=None,
                                                 message_id=mid)), 1)

    def test_create_reduced_same_multiple(self):
        data = {'to': ['testuser', 'testuser'],
                'text': 'Hi there'
                }
        r = self.client.post('/api/message', data, format='json')
        self.assertEqual(r.status_code, status.HTTP_201_CREATED)
        mid = json.loads(r.content)['id']
        self.assertEqual(len(Mail.objects.filter(from_user=self.u,
                                                 to_user=self.u,
                                                 message_id=mid)), 1)

    def test_create_multiple(self):
        data = {'to': ['seconduser', 'thirduser'],
                'text': 'Hi there'
                }
        r = self.client.post('/api/message', data, format='json')
        self.assertEqual(r.status_code, status.HTTP_201_CREATED)
        mid = json.loads(r.content)['id']
        self.assertEqual(len(Mail.objects.filter(from_user=self.u,
                                                 message_id=mid)), 2)

    def test_create_empty_text(self):
        data = {'to': 'testuser',
                'subject': 'Subject'
                }
        r = self.client.post('/api/message', data, format='json')
        self.assertEqual(r.status_code, status.HTTP_201_CREATED)
        mid = json.loads(r.content)['id']
        self.assertEqual(len(Mail.objects.filter(from_user=self.u,
                                                 to_user=self.u,
                                                 message_id=mid)), 1)

        self.assertEqual(len(Message.objects.filter(subject='Subject',
                                                    text='')), 1)


class GetMessageTest(APITestCase):
    def setUp(self):
        self.u, _ = User.objects.get_or_create(username='testuser', password='secret')
        self.u2, _ = User.objects.get_or_create(username='otheruser', password='secret')
        t, _ = Token.objects.get_or_create(user=self.u)
        t2, _ = Token.objects.get_or_create(user=self.u2)
        self.client = APIClient()
        self.client.credentials(HTTP_AUTHORIZATION='Token ' + t.key)

        self.client2 = APIClient()
        self.client2.credentials(HTTP_AUTHORIZATION='Token ' + t2.key)

        data = {'to': 'otheruser',
                'subject': 'Subject',
                'text': 'good text'
               }
        r = self.client.post('/api/message', data, format='json')
        self.mid = json.loads(r.content)['id']

        data = {'to': 'testuser',
                'subject': 'Subject Forbidden',
                'text': 'good text'
               }
        r = self.client2.post('/api/message', data, format='json')
        self.mid2 = json.loads(r.content)['id']

    def test_simple_get(self):
        r = self.client.get('/api/message/%s' % self.mid)

        self.assertEqual(r.status_code, status.HTTP_200_OK)
        self.assertEqual(json.loads(r.content)['subject'], 'Subject')

    def test_non_existent_get(self):
        r = self.client.get('/api/message/10245')

        self.assertEqual(r.status_code, status.HTTP_404_NOT_FOUND)
        self.assertEqual(json.loads(r.content)['detail'], 'No such message')

    def test_forbidden_get(self):
        r = self.client.get('/api/message/%s' % self.mid2)

        self.assertEqual(r.status_code, status.HTTP_403_FORBIDDEN)
        self.assertEqual(json.loads(r.content)['detail'], 'Access denied')


class SendMessageTest(APITestCase):
    def setUp(self):
        self.u, _ = User.objects.get_or_create(username='mysenduser', password='secret')
        self.u2, _ = User.objects.get_or_create(username='myreceiveuser', password='secret')
        t, _ = Token.objects.get_or_create(user=self.u)
        t2, _ = Token.objects.get_or_create(user=self.u2)
        self.client = APIClient()
        self.client.credentials(HTTP_AUTHORIZATION='Token ' + t.key)

        self.client2 = APIClient()
        self.client2.credentials(HTTP_AUTHORIZATION='Token ' + t2.key)

        data = {'to': 'myreceiveuser',
                'subject': 'Subject',
                'text': 'good text'
               }
        r = self.client.post('/api/message', data, format='json')
        self.mid = json.loads(r.content)['id']

    def test_send_message(self):
        r = self.client.post('/api/message/%s' % self.mid, {'action': 'send'}, format='json')
        self.assertEqual(r.status_code, status.HTTP_200_OK)
        self.assertEqual(json.loads(r.content)['detail'], 'Message %s sent' % self.mid)
        self.assertEqual(len(Mail.objects.filter(message_id=self.mid,
                                                 is_draft=True)), 0)
        self.assertEqual(len(Box.objects.filter(mail__message_id__exact=self.mid)), 2)
        self.assertEqual(len(Box.objects.filter(mail__message_id__exact=self.mid,
                                                owner=self.u)), 1)
        self.assertEqual(len(Box.objects.filter(mail__message_id__exact=self.mid,
                                                owner=self.u2)), 1)


class ReadMessageTest(APITestCase):
    def setUp(self):
        self.u, _ = User.objects.get_or_create(username='myreaduser', password='secret')
        t, _ = Token.objects.get_or_create(user=self.u)
        self.client = APIClient()
        self.client.credentials(HTTP_AUTHORIZATION='Token ' + t.key)

        data = {'to': 'myreaduser',
                'subject': 'Subject',
                'text': 'good text'
               }
        r = self.client.post('/api/message', data, format='json')
        self.mid = json.loads(r.content)['id']
        self.client.post('/api/message/%s' % self.mid, {'action': 'send'}, format='json')

    def test_read_message(self):
        r = self.client.post('/api/message/%s' % self.mid, {'action': 'mark_as_read'}, format='json')
        self.assertEqual(json.loads(r.content)['detail'], 'Message %s read' % self.mid)
        self.assertEqual(r.status_code, status.HTTP_200_OK)
        self.assertEqual(len(Mail.objects.filter(message_id=self.mid,
                                                 is_draft=True)), 0)


class UpdateMessageTest(APITestCase):
    def setUp(self):
        self.u, _ = User.objects.get_or_create(username='myupdateuser', password='secret')
        self.u2, _ = User.objects.get_or_create(username='myupdateuserto', password='secret')
        self.u3, _ = User.objects.get_or_create(username='myupdateuserto2', password='secret')

        t, _ = Token.objects.get_or_create(user=self.u)
        self.client = APIClient()
        self.client.credentials(HTTP_AUTHORIZATION='Token ' + t.key)

        data = {'to': 'myupdateuserto',
                'subject': 'First subject',
                'text': 'good text'
               }
        r = self.client.post('/api/message', data, format='json')
        self.mid = json.loads(r.content)['id']

    def test_update_message(self):
        r = self.client.get('/api/message/%s' % self.mid)
        r_before = json.loads(r.content)
        self.assertEqual(r_before['subject'], 'First subject')
        self.assertEqual(r_before['text'], 'good text')
        self.assertEqual(len(Mail.objects.filter(message_id__exact=self.mid)), 1)
        r_before_date = r_before['date']

        data = {'to': ['myupdateuserto', 'myupdateuserto2'],
                'subject': 'Second subject',
                'text': 'new text'
               }

        r = self.client.put('/api/message/%s' % self.mid, data, format='json')

        self.assertEqual(r.status_code, status.HTTP_200_OK)
        self.assertEqual(json.loads(r.content)['detail'], 'Message %s updated' % self.mid)

        r = self.client.get('/api/message/%s' % self.mid)
        r_after = json.loads(r.content)
        self.assertEqual(r_after['subject'], 'Second subject')
        self.assertEqual(r_after['text'], 'new text')
        self.assertNotEqual(str(r_after['date']), str(r_before_date))
        self.assertEqual(len(Mail.objects.filter(message_id__exact=self.mid)), 2)


class DeleteMessageTest(APITestCase):
    def setUp(self):
        self.u, _ = User.objects.get_or_create(username='deletefrom', password='secret')
        self.u2, _ = User.objects.get_or_create(username='deleteto', password='secret')
        t, _ = Token.objects.get_or_create(user=self.u)

        self.client = APIClient()
        self.client.credentials(HTTP_AUTHORIZATION='Token ' + t.key)

        data = {'to': 'deleteto',
                'subject': 'Subject',
                'text': 'good text'
               }
        r = self.client.post('/api/message', data, format='json')
        self.mid_sent = json.loads(r.content)['id']

        self.client.post('/api/message/%s' % self.mid_sent, {'action': 'send'}, format='json')

        data = {'to': 'deleteto',
                'subject': 'Subject notsend',
                'text': 'good text'
               }
        r = self.client.post('/api/message', data, format='json')
        self.mid_draft = json.loads(r.content)['id']

    def test_delete_draft(self):
        r = self.client.delete('/api/message/%s' % self.mid_draft)
        self.assertEqual(r.status_code, status.HTTP_200_OK)
        self.assertEqual(len(Box.objects.filter(owner=self.u,
                                                mail__message_id__exact=self.mid_draft)), 0)
        self.assertEqual(len(Mail.objects.filter(message_id__exact=self.mid_draft)), 0)
        self.assertEqual(len(Message.objects.filter(id=self.mid_draft)), 0)

    def test_delete_sent(self):
        r = self.client.delete('/api/message/%s' % self.mid_sent)
        self.assertEqual(r.status_code, status.HTTP_200_OK)
        self.assertEqual(len(Box.objects.filter(owner=self.u,
                                                mail__message_id__exact=self.mid_sent)), 0)
        self.assertEqual(len(Mail.objects.filter(message_id__exact=self.mid_sent)), 1)
        self.assertEqual(len(Message.objects.filter(id=self.mid_sent)), 1)



class BoxTest(APITestCase):
    def setUp(self):
        self.u, _ = User.objects.get_or_create(username='boxfrom', password='secret')
        self.u2, _ = User.objects.get_or_create(username='boxto', password='secret')
        t, _ = Token.objects.get_or_create(user=self.u)
        t2, _ = Token.objects.get_or_create(user=self.u2)
        self.client = APIClient()
        self.client.credentials(HTTP_AUTHORIZATION='Token ' + t.key)

        self.client2 = APIClient()
        self.client2.credentials(HTTP_AUTHORIZATION='Token ' + t2.key)

        data = {'to': 'boxto',
                'subject': 'Subject',
                'text': 'good text'
               }
        r = self.client.post('/api/message', data, format='json')
        self.mid_from = json.loads(r.content)['id']
        self.client.post('/api/message/%s' % self.mid_from, {'action': 'send'}, format='json')

        data = {'to': 'boxfrom',
                'subject': 'Subject TO',
                'text': 'good text'
               }
        r = self.client2.post('/api/message', data, format='json')
        self.mid_to = json.loads(r.content)['id']
        self.client2.post('/api/message/%s' % self.mid_to, {'action': 'send'}, format='json')

        data = {'to': 'boxto',
                'subject': 'Subject Draft',
                'text': 'good text'
               }
        r = self.client.post('/api/message', data, format='json')
        self.mid_draft = json.loads(r.content)['id']

    def test_get_inbox(self):
        r = self.client.get('/api/box?filter=in')
        self.assertEqual(r.status_code, status.HTTP_200_OK)

        self.assertEqual(len(json.loads(r.content)), 1)
        self.assertEqual(json.loads(r.content)[0]['mail']['message'], self.mid_to)

    def test_get_outbox(self):
        r = self.client.get('/api/box?filter=out')
        self.assertEqual(r.status_code, status.HTTP_200_OK)

        self.assertEqual(len(json.loads(r.content)), 1)
        self.assertEqual(json.loads(r.content)[0]['mail']['message'], self.mid_from)

    def test_get_draftbox(self):
        r = self.client.get('/api/box?filter=draft')
        self.assertEqual(r.status_code, status.HTTP_200_OK)

        self.assertEqual(len(json.loads(r.content)), 1)
        self.assertEqual(json.loads(r.content)[0]['mail']['message'], self.mid_draft)

    def test_incorrect_filtering(self):
        r = self.client.get('/api/box?filter=incorrect')
        self.assertEqual(r.status_code, status.HTTP_400_BAD_REQUEST)

        self.assertEqual(json.loads(r.content)['detail'], 'Filtering not supported. Supported ones: in, out, draft')

    def test_get_without_filtering(self):
        r = self.client.get('/api/box')
        self.assertEqual(r.status_code, status.HTTP_200_OK)
        c = json.loads(r.content)
        self.assertEqual(len(c), 3)
        self.assertEqual(sorted([x['mail']['message'] for x in c]),
                         sorted([self.mid_to, self.mid_draft, self.mid_from]))
