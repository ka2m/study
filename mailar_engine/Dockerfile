FROM python:2.7.11

ADD requirements.txt .
RUN pip install -r requirements.txt

ADD entrypoint /entrypoint
ADD manage.py /srv/manage.py
ADD mailar_engine /srv/mailar_engine

CMD /entrypoint/localserver.sh

