#lang racket

(let ((L1 '(T (HJ (JH KL)) K))
      (L2 '(67 54 (8 9 0) (4 6)))
      (L3 '(K F G H)))
  (list
    (cadr L1)
    (caddr L2)
    (caddr L3)))
