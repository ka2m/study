from enum import Enum


class FilteringTypes(Enum):
    inbox = 'in'
    sent = 'out'
    draft = 'draft'
