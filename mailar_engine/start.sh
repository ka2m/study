#TBD
sleep 6
python manage.py makemigrations registration_api
python manage.py makemigrations mailar_engine
python manage.py migrate
#echo "from django.contrib.auth.models import User; User.objects.create_superuser('vladfau', 'admin@mailar.com', 'pass')" | ./manage.py shell

python manage.py test --keepdb
