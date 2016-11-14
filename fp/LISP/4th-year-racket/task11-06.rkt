#lang racket

;;quicksort
(define (quicksort < l)
    (match l
           ['() '()]
           [(cons x xs)
            (let-values ([(xs-gte xs-lt) (partition (curry < x) xs)])
               (append (quicksort < xs-lt)
                       (list x)
                       (quicksort < xs-gte)))]))

(quicksort < '(1 2 4 5 765 8 12 48 98 123))
