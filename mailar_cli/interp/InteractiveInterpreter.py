from api.APIWrapper import APIWrapper
from api.FilteringTypes import FilteringTypes
from tabulate import tabulate
import getpass
from cmd import Cmd
from BaseInterpreter import BaseInterpreter


class InteractiveInterpreter(BaseInterpreter, Cmd):
    api_wrapper = None
    settings = None
    prompt = 'MAILAR> '
    
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

    def __yes_or_no(self, message, default_yes=True):
        yes = {'yes', 'y', 'ye', ''}
        no = {'no', 'n'}

        def_view = '(Y/n)' if default_yes else '(y/N)'

        choice_from = yes if default_yes else no
        not_choice_from = no if default_yes else yes

        choice = raw_input('%s %s' % (message, def_view)).lower()

        return choice in choice_from or choice not in not_choice_from


    def run(self):
        self.cmdloop()

    def __get_login_data(self):
        login = raw_input('Login: ')
        password = getpass.getpass('Password: ')
        self.api_wrapper.username = login
        self.api_wrapper.password = password

    def set_endpoint(self):
        self.api_wrapper.api_endpoint = raw_input('Mailar engine URL: ')
        print tabulate([["Endpoint", self.api_wrapper.api_endpoint]])
        BaseInterpreter.store_endpoint(self.api_wrapper.api_endpoint)

    def register(self):
        self.__get_login_data()
        hc, data = BaseInterpreter.register(self)

        header = 'Detail'
        if type(data) is dict and 'token' in data.keys():
            header = 'Token'
            message = data['token']
        elif type(data) is dict and 'detail' in data.keys():
            message = data['detail']
        else:
            header = 'Error'
            message = data

        print tabulate([["Code", hc], [header, message]])

    def login(self):
        self.__get_login_data()
        hc, data = BaseInterpreter.login(self)
        
        header = 'Detail'
        if type(data) is dict and 'token' in data.keys():
            header = 'Token'
            message = data['token']
        elif type(data) is dict and 'detail' in data.keys():
            message = data['detail']
        else:
            header = 'Error'
            message = data

        print tabulate([["Code", hc], [header, message]])

    def create(self, to=None, subject=None, text=None):
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

        hc, data = BaseInterpreter.create_draft(self, to, subject, text)

        if self.__yes_or_no('Send'):
            header = 'Detail'
            if type(data) is dict:
                if 'detail' in data.keys():
                    message = data['detail']
                elif 'id' in data.keys():
                    header = 'Draft Id'
                    message = data['id']
                else:
                    message = data
            else:
                header = 'Error'
                message = data
            print tabulate([["Code", hc], [header, message]])
        elif choice in yes:
            hc, data = BaseInterpreter.send(self, to, subject, text)

            header = 'Detail'
            if type(data) is dict:
                if 'detail' in data.keys():
                    message = data['detail']
                elif 'id' in data.keys():
                    header = 'Message Id'
                    message = data['id']
                else:
                    message = data
            else:
                header = 'Error'
                message = data

            print tabulate([["Code", hc], [header, message]])

    def create_draft(self, to=None, subject=None, text=None):
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
        hc, data = BaseInterpreter.create_draft(self, to, subject, text)
        header = 'Detail'
        if type(data) is dict:
            if 'detail' in data.keys():
                message = data['detail']
            elif 'id' in data.keys():
                header = 'Draft Id'
                message = data['id']
            else:
                message = data
        else:
            header = 'Error'
            message = data
        print tabulate([["Code", hc], [header, message]])

    def send_draft(self, message_id=None):
        message_id = raw_input('Id: ')
        hc, data = BaseInterpreter.send_draft(self, message_id)

        header = 'Detail'
        if type(data) is dict:
            if 'detail' in data.keys():
                message = data['detail']
            else:
                message = data
        else:
            header = 'Error'
            message = data

        print tabulate([["Code", hc], [header, message]])

    def box(self, ft):
        hc, data = BaseInterpreter.box(self, ft)
        if type(data) is list:
            dest = 'To'

            cols = ['id']
            if ft == FilteringTypes.inbox:
                cols.append('from_user')
                dest = 'From'
            else:
                cols.append('to_user')
            cols.extend(['subject', 'date'])

            table = [['No', dest, 'Subject', 'Date']]
            for item in data:
                d = []
                for ri in cols:
                    if item['is_new']:
                        d.append('{0}{1}{2}'.format('\033[91m',
                                                    item[ri],
                                                    '\033[0m'))
                    else:
                        d.append(item[ri])
                table.append(d)
            print tabulate(table, headers="firstrow")
        else:
            header = 'Error'
            message = data
            if type(data) is dict and 'detail' in data.keys():
                message = data['detail']
            print tabulate([["Code", hc], [header, message]])

    def delete(self, message_id=None):
        message_id = raw_input('Id: ')
        hc, data = BaseInterpreter.delete(self, message_id)
        header = 'Detail'
        if type(data) is dict:
            if 'detail' in data.keys():
                message = data['detail']
            else:
                message = data
        else:
            header = 'Error'
            message = data
        print tabulate([["Code", hc], [header, message]])

    def read(self, message_id=None):
        message_id = raw_input('Id: ')
        hc, data = BaseInterpreter.read(self, message_id)

        header = 'Detail'
        if type(data) is dict:
            if 'text' in data.keys():
                message = data['text']
                header = 'Message'
            else:
                message = data
        else:
            header = 'Error'
            message = data
        print tabulate([["Code", hc], [header, message]])

    def update(self, message_id=None, to=None, subject=None, text=None):
        message_id = raw_input('Id: ')
        hc, data = BaseInterpreter.get(self, message_id)

        header = 'Detail'
        if hc != 200:
            if type(data) is dict:
                if 'detail' in data.keys():
                    message = data['detail']
                else:
                    message = data
            else:
                header = 'Error'
                message = data
            print tabulate([["Code", hc], [header, message]])
        else:
            hc, _drafts_box = BaseInterpreter.box(self, FilteringTypes.draft)
            if hc != 200:
                if type(data) is dict:
                    if 'detail' in data.keys():
                        message = data['text']
                    else:
                        message = data
                else:
                    header = 'Error'
                    message = data
                print tabulate([["Code", hc], [header, message]])
            to = filter(lambda x: x['id'] == message_id, _drafts_box)[0]['to_user']
            new_to = to
            if self.__yes_or_no('Change To? To: %s' % to):
                new_to = raw_input('To: ')
            new_subject = data['subject']
            if self.__yes_or_no('Change Subject? Subject: %s' % data['subject']):
                new_subject = raw_input('Subject: ')
            new_text = data['text']
            if self.__yes_or_no('Change Text? Text: %s' % data['text']):
                new_text = raw_input('Subject: ')
            hc, data = BaseInterpreter.update(message_id, new_to, new_subject, new_text)
            header = 'Detail'
            if type(data) is dict:
                if 'detail' in data.keys():
                    message = data['detail']
                else:
                    message = data
            else:
                header = 'Error'
                message = data
            print tabulate([["Code", hc], [header, message]])

    def do_set_endpoint(self, line):
        return self.set_endpoint()

    def do_login(self, line):
        return self.login()

    def do_register(self, line):
        return self.register()

    def do_create(self, line):
        return self.create()

    def do_create_draft(self, line):
        return self.create_draft()

    def do_send_draft(self, line):
        return self.send_draft()

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

    def do_delete(self, line):
        return self.delete()

    def do_read(self, line):
        return self.read()

    def do_update(self, line):
        return self.update()
