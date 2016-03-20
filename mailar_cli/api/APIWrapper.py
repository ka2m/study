from MailarConnector import MailarConnector as mc


class APIWrapper:

    view_path = "view"
    message = "message"

    def __init__(self, user=None, password=None, token=None):
        self.connector = mc(user, password, token)

    def get_view(self):
        return self.connector.get(self.view_path)