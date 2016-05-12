import requests
import base64
import json


def obligatory_token(func):
    def check(_func, *args, **kwargs):
        def wrapper(self, *args, **kwargs):
            if self.token is None:
                _, t = self.login()
            return _func(self, *args, **kwargs)
        return wrapper
    return check(func)


def mid_to_int(func):
    def check(_func, *args, **kwargs):
        def wrapper(self, message_id, *args, **kwargs):
            if type(message_id) is not int:
                message_id = int(message_id)
            return _func(self, message_id, *args, **kwargs)
        return wrapper
    return check(func)


class APIWrapper:
    username = None
    password = None
    api_endpoint = None
    token = None
    token_auth = {'Authorization': 'Token %s' % token}

    class NoAuthError(Exception):
        pass

    def __init__(self, api_endpoint=None, token=None, username=None, password=None):
        self.api_endpoint = api_endpoint
        if token is None:
            self.username = username
            self.password = password
        else:
            self.token = token
            self.token_auth = {'Authorization': 'Token %s' % self.token}

    def set_token(self, value):
        self.token = value
        self.token_auth = {'Authorization': 'Token %s' % self.token}

    def register(self):
        url = '%s/api/register' % self.api_endpoint

        r = requests.post(url, json={'auth': base64.b64encode('%s:%s' % (self.username, self.password))})
        return r.status_code, r.content

    def login(self):
        url = '%s/api/login' % self.api_endpoint

        r = requests.post(url, auth=(self.username, self.password))
        try:
            self.token = json.loads(r.content)['token']
            self.token_auth = {'Authorization': 'Token %s' % self.token}
        except:
            pass

        return r.status_code, r.content

    @obligatory_token
    def create_message(self, to=None, subject=None, text=None):
        url = '%s/api/message' % self.api_endpoint

        data = dict(zip(['to', 'subject', 'text'],
                        [to, subject, text]))

        r = requests.post(url,
                          json=data,
                          headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    @mid_to_int
    def get(self, message_id):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        r = requests.get(url,
                         headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    @mid_to_int
    def send(self, message_id):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        r = requests.post(url,
                          json={'action': 'send'},
                          headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    @mid_to_int
    def read(self, message_id):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        r = requests.post(url,
                          json={'action': 'mark_as_read'},
                          headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    @mid_to_int
    def update(self, message_id, to=None, subject=None, text=None):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        data = dict(zip(['to', 'subject', 'text'],
                        [to, subject, text]))

        r = requests.put(url,
                         json=data,
                         headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    @mid_to_int
    def delete(self, message_id):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        r = requests.delete(url,
                            headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    def box(self, filter_type=None):
        if filter_type is not None:
            url = '%s/api/box?filter=%s' % (self.api_endpoint, filter_type)
        else:
            url = '%s/api/box' % self.api_endpoint

        r = requests.get(url,
                         headers=self.token_auth)

        return r.status_code, r.content
