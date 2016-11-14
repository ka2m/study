#lang racket
(require racket/trace)

;;quicksort
(define (quicksort l)
    (let quick-acc ((tosort l)
                    (acc '()))
      (if (or (null? tosort)
              (null? (cdr tosort)))
          (append tosort acc)
          (let* ((pivot (car tosort))
                 (tosort (cdr tosort))
                 (acc (append (list pivot) (quicksort (filter ((curry <=) pivot) tosort)) acc)))
                (quick-acc (filter ((curry >) pivot) tosort) acc)))))

(trace quicksort)
(quicksort '(1 34 58 21 2 3 80 6))
