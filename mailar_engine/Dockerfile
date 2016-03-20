FROM python:2.7.11

ADD requirements.txt .

RUN pip install -r requirements.txt

WORKDIR /srv
CMD sh /srv/start.sh

