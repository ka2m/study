# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
from django.shortcuts import render
from ra.funcs import add_car
from ra.models import Road, PointOfInterest, Car, RoadLoadEvent


def addcar(request):
    car_name = request.POST['name']
    car_speed = float(request.POST['speed'])
    car_from = int(request.POST['car_from'])
    car_to = int(request.POST['car_to'])
    hr_from = int(request.POST['hrstart'])
    min_from = int(request.POST['minstart'])
    add_car(car_name,
            car_speed,
            car_from,
            car_to,
            hr_from,
            min_from,
            0)
    context = {}
    context['msg'] = u'Добавлено!'
    return render(request, 'added.html', context)


def addroad(request):
    road_name = request.POST['road_name']
    road_length = request.POST['road_length']
    from_id = request.POST['rasfrom']
    to_id = request.POST['rasto']
    context = {}
    if not road_name:
        context['msg'] = u'Имя не может быть пустым'
    elif from_id == to_id:
        context['msg'] = u'Начальный и конечный пункт совпадают'
    elif not float(road_length):
        context['msg'] = u'Нулевая длина!'
    else:
        try:
            Road.objects.get(point_from_id=from_id,
                             point_to_id=to_id)
            context['msg'] = u'Уже существует!'
        except Road.DoesNotExist:
            try:
                Road.objects.get(point_from_id=to_id,
                                 point_to_id=from_id)
                context['msg'] = u'Уже существует!'
            except Road.DoesNotExist:
                context['msg'] = u'Добавлено!'
                Road(name=road_name,
                     length=road_length,
                     point_from=PointOfInterest.objects.get(pk=from_id),
                     point_to=PointOfInterest.objects.get(pk=to_id)).save()
    return render(request, 'added.html', context)


def addplace(request):
    pname = request.POST['place_name']
    context = {}
    if not pname:
        context['msg'] = u'Имя не может быть пустым'
    else:
        try:
            PointOfInterest.objects.get(name=pname)
            context['msg'] = u'Уже существует!'
        except PointOfInterest.DoesNotExist:
            context['msg'] = u'Добавлено!'
            PointOfInterest(name=pname).save()
    return render(request, 'added.html', context)


def viewstat(request):
    road_id = request.POST['analroad']
    from_hr = request.POST['from_hr']
    from_min = request.POST['from_min']
    to_hr = request.POST['to_hr']
    to_min = request.POST['to_min']
    from_sec = int(from_hr) * 3600 + int(from_min) * 60
    to_sec = int(to_hr) * 3600 + int(to_min) * 60

    step = 120
    prev_time = from_sec
    next_time = prev_time + step

    steps = []

    while prev_time <= to_sec:
        shr = int(prev_time / 3600)
        smin = int((prev_time - (shr * 3600)) / 60)
        steps.append(("%s:%s" % (shr, smin if len(str(smin)) == 2 else '0%s' % smin),
                     RoadLoadEvent.objects.filter(road_id=road_id,
                                                  load_started__lte=prev_time,
                                                  load_ended__gte=next_time).count()))
        prev_time = next_time
        next_time += step

    y = [x[1] for x in steps]
    labels = [x[0] for x in steps]
    x = range(len(y))
    print y, labels, x
    plt.bar(x, y, 1.0, color="blue")
    plt.xticks(x, labels, rotation='vertical')
    plt.savefig('static/fig.png')
    return render(request, 'chart.html', {})


def index(request):
    context = {'count_points': PointOfInterest.objects.count(),
               'count_roads': Road.objects.count(),
               'count_loads': RoadLoadEvent.objects.count(),
               'count_cars': Car.objects.count(),
               'poi': PointOfInterest.objects.all(),
               'roads': Road.objects.all()}
    return render(request, 'index.html', context)
