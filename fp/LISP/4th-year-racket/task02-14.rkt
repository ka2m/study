#lang racket

(let ((L '(A B C D (E (F () (() X)) G H))))
  (car                    ; get X
    (cdar                 ; get (X)
      (cddr               ; get (() X)
        (cadar            ; get (F () (() X))
          (cddddr L)))))) ; get (E (F () (() X))

