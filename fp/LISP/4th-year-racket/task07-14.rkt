#lang racket

(define (func L1 L2)
  (if (not (pair? (car L1)))
      (cons L2
            (cdr L1))
      (cons (car L1)
            (cons L2
                  (cddr L1)))))

(func '(1 2 3 4) 5)
(func '('(1) 2 3 4) 5)
