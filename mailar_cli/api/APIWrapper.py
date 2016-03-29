import requests
import base64
import json


def obligatory_token(func):
    def check(func):
        def wrapper(self, *args):
            if self.token is None:
                _, t = self._login()
            return func(self, *args)
        return wrapper
    return check(func)


class APIWrapper:

    login = None
    password = None
    api_endpoint = None
    token = None
    token_auth = {'Authorization': 'Token %s' % token}
    
    class NoEndpointProvidedError(Exception):
        pass

    class NoAuthError(Exception):
        pass

    def __init__(self, api_endpoint, token=None, username=None, password=None):
        if api_endpoint is None:
            raise self.NoEndpointProvidedError
        self.api_endpoint = api_endpoint
        if token is None:
            if username is None or password is None:
                raise self.NoAuthError
            else:
                self.login = username
                self.password = password
        else:
            self.token = token
            self.token_auth = {'Authorization': 'Token %s' % self.token}

    def _register(self):
        url = '%s/api/register' % self.api_endpoint

        r = requests.post(url, json={'auth': base64.b64encode('%s:%s' % (self.login, self.password))})
        return r.status_code, r.content

    def _login(self):
        url = '%s/api/login' % self.api_endpoint

        r = requests.post(url, auth=(self.login, self.password))

        self.token = json.loads(r.content)['token']
        self.token_auth = {'Authorization': 'Token %s' % self.token}

        return r.status_code, r.content

    @obligatory_token
    def _create_message(self, to=None, subject=None, text=None):
        url = '%s/api/message' % self.api_endpoint

        data = dict(zip(['to', 'subject', 'text'],
                        [to, subject, text]))

        r = requests.post(url,
                          json=data,
                          headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    def _get(self, message_id):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        r = requests.get(url,
                         headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    def _send(self, message_id):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        r = requests.post(url,
                          json={'action': 'send'},
                          headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    def _read(self, message_id):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        r = requests.post(url,
                          json={'action': 'mark_as_read'},
                          headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    def _update(self, message_id, to=None, subject=None, text=None):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        data = dict(zip(['to', 'subject', 'text'],
                        [to, subject, text]))

        r = requests.put(url,
                         json=data,
                         headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    def _delete(self, message_id):
        url = '%s/api/message/%d' % (self.api_endpoint, message_id)

        r = requests.delete(url,
                            headers=self.token_auth)
        return r.status_code, r.content

    @obligatory_token
    def _box(self, filter_type=None):
        if filter_type is not None:
            url = '%s/api/box?filter=%s' % (self.api_endpoint, filter_type)
        else:
            url = '%s/api/box' % self.api_endpoint

        r = requests.get(url,
                         headers=self.token_auth)

        return r.status_code, r.content
