from api.APIWrapper import APIWrapper
from api.FilteringTypes import FilteringTypes
import json
import os
from os.path import expanduser


class BaseInterpreter:
    api_wrapper = None
    settings = None

    def __init__(self):
        self.api_wrapper = APIWrapper()

    def run(self):
        pass

    @staticmethod
    def store_endpoint(new):
        home = expanduser('~')
        settings_file = os.path.join(home, '.mailar')
        if os.path.exists(settings_file):
            with open(settings_file, 'r') as f:
                try:
                    settings = json.loads('\n'.join(f.readlines()))
                    settings['endpoint'] = new
                except:
                    settings = dict()
                    settings['endpoint'] = new
        else:
            settings = dict()
            settings['endpoint'] = new
        with open(settings_file, 'w') as f:
            f.writelines(json.dumps(settings))

    @staticmethod
    def load_settings():
        home = expanduser('~')
        settings_file = os.path.join(home, '.mailar')
        if os.path.exists(settings_file):
            with open(settings_file, 'r') as f:
                try:
                    return json.loads('\n'.join(f.readlines()))
                except:
                    print 'No default config loaded'
        return None

    def register(self):
        try:
            sc, content = self.api_wrapper.register()
            if sc == 201:
                self.api_wrapper.set_token(json.loads(content)['token'])
                return 'Account registered. Your token: %s' % self.api_wrapper.token
            elif sc == 400:
                return 'Bad credentials were passed'
            elif sc == 409:
                return 'User already exists'
        except Exception as e:
            return e

    def login(self):
        try:
            sc, content = self.api_wrapper.login()
            if sc == 200:
                self.api_wrapper.set_token(json.loads(content)['token'])
                return 'Token: %s' % self.api_wrapper.token
            else:
                return json.loads(content)['detail']
        except Exception as e:
            return e

    def send(self, to=None, subject=None, text=None):
        try:
            if ',' in to:
                to = [x for x in to.split(',') if len(x)]
            sc, content = self.api_wrapper.create_message(to, subject, text)
            if sc == 201:
                message_id = json.loads(content)['id']
                if to is not None and len(to):
                    _sc, _content = self.api_wrapper.send(message_id)
                    return json.loads(_content)['detail']
                else:
                    return 'Saved as draft. Id: %s' % message_id
            else:
                return json.loads(content)['detail']
        except Exception as e:
            return e

    def box(self, ft):
        try:
            sc, content = self.api_wrapper.box(filter_type=ft.value)
            if sc == 200:
                parsed_content = json.loads(content)
                for m in parsed_content:
                    message_id = m['mail']['message']
                    _sc, _content = self.api_wrapper.get(message_id)
                    if _sc != 200:
                        return json.loads(_content)['detail']
                    m['mail']['message'] = json.loads(_content)
                    m['mail']['message']['id'] = message_id
                dest = 'from' if ft == FilteringTypes.inbox else 'to'
                return map(lambda x: {'dest': x['mail']['from_user']['username']
                                            if ft == FilteringTypes.inbox else
                (x['mail']['to_user']['username'] if x['mail']['to_user'] is not None else ''),
                                      'date': x['mail']['message']['date'],
                                      'id': x['mail']['message']['id'],
                                      'subject': x['mail']['message']['subject'],
                                      'is_new': x['is_new']}, parsed_content)
            else:
                return json.loads(content)['detail']
        except Exception as e:
            return e
