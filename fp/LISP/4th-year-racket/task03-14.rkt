#lang racket

(let ((my-e (cons 'E
                  (cons
                    (cons 'F
                          (cons '()
                                (cons
                                  (cons '()
                                        (cons 'X
                                              '()))
                                  '())))
                    (cons 'G
                          (cons 'H
                                '()))))))

  (cons 'A
        (cons 'B
              (cons 'C
                    (cons 'D
                          (cons my-e
                                '()))))))

