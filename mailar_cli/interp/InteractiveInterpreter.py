from api.APIWrapper import APIWrapper
from api.FilteringTypes import FilteringTypes
import json
import getpass
from cmd import Cmd
from BaseInterpreter import BaseInterpreter


class InteractiveInterpreter(BaseInterpreter, Cmd):
    api_wrapper = None
    settings = None
    prompt = 'MAILAR> '

    def set_endpoint(self):
        self.api_wrapper.api_endpoint = raw_input('Mailar engine URL: ')
        print self.api_wrapper.api_endpoint
        BaseInterpreter.store_endpoint(self.api_wrapper.api_endpoint)

    def __get_login_data(self):
        login = raw_input('Login: ')
        password = getpass.getpass('Password: ')
        self.api_wrapper.username = login
        self.api_wrapper.password = password

    def register(self):
        self.__get_login_data()
        print BaseInterpreter.register(self)

    def login(self):
        self.__get_login_data()
        print BaseInterpreter.login(self)

    def __init__(self):
        Cmd.__init__(self)
        BaseInterpreter.__init__(self)
        self.api_wrapper = APIWrapper()
        self.settings = BaseInterpreter.load_settings()
        if self.settings is not None and 'endpoint' in self.settings.keys():
            self.intro = 'Welcome to Mailar CLI. Don\'t forget to set your credentials'
            self.api_wrapper.api_endpoint = self.settings['endpoint']
        else:
            self.intro = 'Welcome to Mailar CLI. Don\'t forget to set endpoint of server and your credentials'

    def run(self):
        self.cmdloop()

    def send(self, to=None, subject=None, text=None):
        print 'End sequence is "@q!"'
        to = raw_input('To: ')
        subject = raw_input('Subject: ')
        print 'Text: '
        text = []
        while True:
            try:
                new_item = raw_input('> ')
                text.append(new_item)
                if new_item.endswith('@q!'):
                    text = '\n'.join(text)[0:-3]
                    break
            except:
                pass
        print BaseInterpreter.send(self, to, subject, text)

    def box(self, ft):
        print BaseInterpreter.box(self, ft)

    def do_set_endpoint(self, line):
        return self.set_endpoint()

    def do_login(self, line):
        return self.login()

    def do_register(self, line):
        return self.register()

    def do_send(self, line):
        return self.send()

    def do_exit(self, line):
        return True

    def do_EOF(self, line):
        return True

    def do_inbox(self, line):
        return self.box(FilteringTypes.inbox)

    def do_sent(self, line):
        return self.box(FilteringTypes.sent)

    def do_drafts(self, line):
        return self.box(FilteringTypes.draft)
