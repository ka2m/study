#lang racket

(let ((L1 '(T (HJ (JH KL)) K))
      (L2 '(67 54 (8 9 0) (4 6)))
      (L3 '(K F G H)))
  (append
    (list
      (car L1)
      (caddr L1))
    (list
      (car L2)
      (cadr L2))
    (cdddr L2)
    (list
      (car L3)
      (cadr L3))
    (cdddr L3)))
