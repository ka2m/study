from api import APIWrapper as api


endpoint = 'http://192.168.99.100:8000/api'
user = 'vladique'
password = 'passw'

#token = b1a7d5b85a9afd9d919d3e011489c9210cff64b
mc = api.APIWrapper(endpoint, user, password)
print mc.get_view()