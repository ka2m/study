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
            hc, content = self.api_wrapper.register()
            if hc == 201:
                self.api_wrapper.set_token(json.loads(content)['token'])
            return hc, json.loads(content)
        except Exception as e:
            return 0, e

    def login(self):
        try:
            hc, content = self.api_wrapper.login()
            if hc == 200:
                self.api_wrapper.set_token(json.loads(content)['token'])
            return hc, json.loads(content)
        except Exception as e:
            return 0, e

    def send(self, to=None, subject=None, text=None):
        try:
            if ',' in to:
                to = [x for x in to.split(',') if len(x)]
            hc, content = self.api_wrapper.create_message(to, subject, text)
            if hc == 201 and to is not None and len(to):
                message_id = json.loads(content)['id']
                _hc, _content = self.api_wrapper.send(message_id)
                return _hc, json.loads(_content)
            else:
                return hc, json.loads(content)
        except Exception as e:
            return 0, e

    def create_draft(self, to=None, subject=None, text=None):
        try:
            if ',' in to:
                to = [x for x in to.split(',') if len(x)]
            hc, content = self.api_wrapper.create_message(to, subject, text)
            return hc, json.loads(content)
        except Exception as e:
            return 0, e

    def send_draft(self, message_id=None):
        try:
            hc, content = self.api_wrapper.send(message_id)
            return hc, json.loads(content)
        except Exception as e:
            return 0, e

    def delete(self, message_id=None):
        try:
            hc, content = self.api_wrapper.delete(message_id)
            return hc, json.loads(content)
        except Exception as e:
            return 0, e

    def get(self, message_id):
        try:
            hc, content = self.api_wrapper.get(message_id)
            return hc, json.loads(content)
        except Exception as e:
            return 0, e

    def read(self, message_id):
        try:
            hc, content = self.api_wrapper.get(message_id)
            self.api_wrapper.read(message_id)
            return hc, json.loads(content)
        except Exception as e:
            return 0, e

    def update(self, message_id, to=None, subject=None, text=None):
        try:
            hc, content = self.api_wrapper.update(message_id, to, subject, text)
            return hc, json.loads(content)
        except Exception as e:
            return 0, e

    def box(self, ft):
        try:
            hc, content = self.api_wrapper.box(filter_type=ft.value)
            if hc == 200:
                parsed_content = json.loads(content)
                for m in parsed_content:
                    message_id = m['mail']['message']
                    _hc, _content = self.api_wrapper.get(message_id)
                    if _hc != 200:
                        return _hc, json.loads(_content)
                    m['mail']['message'] = json.loads(_content)
                    m['mail']['message']['id'] = message_id
                dest = 'from_user' if ft == FilteringTypes.inbox else 'to_user'
                return hc, map(lambda x: {dest: x['mail']['from_user']['username']
                                                if ft == FilteringTypes.inbox else
                (x['mail']['to_user']['username'] if x['mail']['to_user'] is not None else ''),
                                      'date': x['mail']['message']['date'],
                                      'id': x['mail']['message']['id'],
                                      'subject': x['mail']['message']['subject'],
                                      'is_new': x['is_new']}, parsed_content)
            else:
                return hc, json.loads(content)
        except Exception as e:
            return 0, e
