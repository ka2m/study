#lang racket

(let ((L1 '(T (HJ (JH KL)) K))
      (L2 '(67 54 (8 9 0) (4 6)))
      (L3 '(K F G H)))
  (and
    (number? (cadr L1))
    (not (pair? (caddr L2)))
    (list? (caddr L3))))
