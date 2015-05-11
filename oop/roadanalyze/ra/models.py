from django.db import models


class PointOfInterest(models.Model):
    name = models.CharField(max_length=20)


class Road(models.Model):
    name = models.CharField(max_length=20)
    length = models.FloatField()
    point_from = models.ForeignKey(PointOfInterest, null=True, blank=True, related_name='point_from')
    point_to = models.ForeignKey(PointOfInterest, null=True, blank=True, related_name='point_to')


class Car(models.Model):
    drive_from = models.ForeignKey(PointOfInterest, related_name='drive_from')
    drive_to = models.ForeignKey(PointOfInterest, related_name='drive_to')
    speed = models.FloatField()
    starting_time = models.BigIntegerField()
    name = models.CharField(max_length=10)


class RoadLoadEvent(models.Model):
    road = models.ForeignKey(Road)
    load_started = models.BigIntegerField()
    load_ended = models.BigIntegerField()
