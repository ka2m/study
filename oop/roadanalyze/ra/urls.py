from django.conf.urls import url
from ra import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^addcar$', views.addcar, name='addcar'),
    url(r'^addplace$', views.addplace, name='addplace'),
    url(r'^addroad$', views.addroad, name='addroad'),
    url(r'^viewstat$', views.viewstat, name='viewstat')
]
