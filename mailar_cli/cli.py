from api import APIWrapper as api


endpoint = 'http://192.168.99.100:8000'
user = 'vladique'
password = 'passw'

mc = api.APIWrapper(endpoint, token="b31a89ac167e559861855103dafa7e3964838283")
#print mc._login()

user2 = 'vladfau'
password2 = 'pass'

mc2 = api.APIWrapper(endpoint, username=user2, password=password2)


print mc._box('out')
