#lang racket

(define (y N)
  (define (ij-func i j)
    (+ (log i) (/ i j)))
  (define (y-iter i j isum esum)
    (cond ((> i N) esum)
          ((> j N) (y-iter (+ i 1) 1 0 (+ esum isum)))
          (else    (y-iter i (+ j 1) (+ isum (ij-func i j)) esum))))
  (y-iter 1 1 0 0))

(y 5)
(y 10)
