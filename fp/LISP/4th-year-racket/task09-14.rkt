#lang racket

;; reverse the list
(define (rev lst)
    (define (rev-int lst res)
        (if (null? lst)
             res
            (rev-int (cdr lst)
                     (cons (car lst) res))))
    (rev-int lst '()))

;; Check that element is in list
(define (element? x lst)
    (cond ((null? lst) #f)
          ((eq? x (car lst)) #t)
          (else (element? x (cdr lst)))))

;; remove element from list if found
(define (remove x lst)
    (define (remove-int x lst res)
        (if (null? lst)
            res
            (if (eq? x (car lst))
                (remove-int x (cdr lst) res)
                (remove-int x (cdr lst) (cons (car lst) res)))))
    (rev (remove-int x lst '())))

;; substract set s2 from set s1. not reflexive!
(define (substract s1 s2)
  (cond ((null? s2) s1)
        ((element? (car s2) s1) (substract (remove (car s2) s1) (cdr s2)))
        (else (substract s1 (cdr s2)))))

(substract '(1 2 3 4 5) '(2 3 4))
(substract '(1 2 3 4 5) '(2 6 4))
(substract '(1 2 3 4 5) '())
(substract '(1 2 3 4 5) '(1 2 3 4 5))
(substract '(1 2 3 4 5) '(1))
(substract '(1 2 3 4 5) '(5))

