#!/bin/bash
b64=$(python -c "import base64; print base64.b64encode('vladique:passw')")

# sign up
curl -X POST -d="${b64}"  http://192.168.99.100:8000/api/register/

# if you forgot your token
curl -X POST -u vladique:passw  http://192.168.99.100:8000/api/login/

# vladfau is admin
curl -X POST http://192.168.99.100:8000/api/message/ -H "Authorization: Token ${b64}" -d '{"to": ["vladfau"], "subject": "Hello world!", "text": "I wanna take you away!"}'
curl http://192.168.99.100:8000/api/message/outgoing -H "Authorization: Token ${b64}"
curl http://192.168.99.100:8000/api/message/1 -H "Authorization: Token ${b64}"


# cli is really in progress
