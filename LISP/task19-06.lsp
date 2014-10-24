(print
  (let ((L1 '(T Y D E F (NL KM LM) JL))
        (L2 '(+ 2 3))
        (L3 '(* (+ 6 8) (- 70 8))))
    (and
      (numberp (caddr (cdddr L1)))
      (atom (cadr L2))
      (listp (cadr L3)))))
