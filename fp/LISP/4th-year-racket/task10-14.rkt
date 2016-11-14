#lang racket

;; reverse the list
(define (rev lst)
    (define (rev-int lst res)
        (if (null? lst)
             res
            (rev-int (cdr lst)
                     (cons (car lst) res))))
    (rev-int lst '()))

(define (main lst lvl)
    (define (remove-at-lvl lst lvl cur res)
        (if (null? lst)
            (rev res)
            (if (list? (car lst))
                (if (eq? lvl cur)
                    (remove-at-lvl (cdr lst) lvl cur res)
                    (remove-at-lvl (cdr lst)
                                   lvl
                                   cur
                                   (cons (remove-at-lvl (car lst)
                                                         lvl
                                                         (+ cur 1)
                                                         '())
                                         res)))
                (remove-at-lvl (cdr lst) lvl cur (cons (car lst) res)))))
    (remove-at-lvl lst lvl 0 '()))

(main '(1 (2 (9 5 4)) 3 (4 (9 (9) 9))) 2)
