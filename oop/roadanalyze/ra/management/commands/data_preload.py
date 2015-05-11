from ra.models import PointOfInterest, Road
from django.core.management.base import NoArgsCommand
from ra import funcs


class Command(NoArgsCommand):
    def handle_noargs(self, **options):
        points = ['Del Apierro',
                  'Benjtown',
                  'Coherence Village',
                  'Demington',
                  'Elberdo']
        for point in points:
            PointOfInterest(name=point).save()

        roads = [('Meadown Interstate',
                  10.0,
                  PointOfInterest.objects.get(name=points[0]),
                  PointOfInterest.objects.get(name=points[1])),
                 ('Hollywag Road',
                  25.0,
                  PointOfInterest.objects.get(name=points[0]),
                  PointOfInterest.objects.get(name=points[3])),
                 ('Bachelor Path',
                  5.0,
                  PointOfInterest.objects.get(name=points[1]),
                  PointOfInterest.objects.get(name=points[2])),
                 ('Some Road',
                  6.0,
                  PointOfInterest.objects.get(name=points[3]),
                  PointOfInterest.objects.get(name=points[2])),
                 ('Escape Route',
                  7.0,
                  PointOfInterest.objects.get(name=points[3]),
                  PointOfInterest.objects.get(name=points[4]))
                 ]

        for road in roads:
            Road(**dict(zip(['name', 'length', 'point_from', 'point_to'], road))).save()
        funcs.add_car("RedCar", 40, 1, 3, 10, 0, 0)
        funcs.add_car("BlueCar", 40, 1, 3, 10, 2, 0)
