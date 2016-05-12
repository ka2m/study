"""mailar_engine URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.9/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
from mailar_engine import views


urlpatterns = [
    url(r'^api/register', views.register),
    url(r'^api/login', views.login_view),
    url(r'^api/register/', views.register),
    url(r'^api/login/', views.login_view),
    url(r'^api/message$', views.create_message),
    url(r'^api/message/$', views.create_message),
    url(r'^api/message/(?P<message_id>\w+)', views.message),
    url(r'^api/message/(?P<message_id>\w+)', views.message),
    url(r'^api/box', views.box),
    url(r'^api/box/', views.box)
]
