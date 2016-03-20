import requests
import json


class MailarConnector:

    def __init__(self, endpoint, user=None, password=None, token=None):
        self.api_endpoint = endpoint
        if user is None and password is None:
            if token is not None:
                self.token = token
            else:
                raise Exception("Neither token, nor credentials are passed")
        else:
            self.token = self.get_token(user, password)

    def get_token(self, user, password):
        res = requests.post('%s/login/' % self.api_endpoint, auth=(user, password))
        if res.status_code == 200:
            return json.loads(res.content)["token"]
        else:
            print json.loads(res.content)["detail"]
            error_info = json.loads(res.content)["detail"]
            raise Exception("Unable to login: %s" % error_info)

    def get(self, path):
        r = requests.get('%s/%s/' % (self.api_endpoint, path),
                         headers={'Authorization': 'Token %s' % self.token})
        return r.content, r.status_code

    def post(self, path, payload=None, json=None):
        r = requests.post('%s/%s/' % (self.api_endpoint, path),
                          data=payload,
                          json=json,
                          headers={'Authorization': 'Token %s' % self.token})
        return r.content, r.status_code