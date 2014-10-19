(print
  (let ( (L1 '(T Y D E F (NL KM LM) JL))
         (L2 '(+ 2 3))
         (L3 '(* (+ 6 8) (- 70 8))))
    (and
      (numberp (cdddr L1))
      (atom L2)
      (listp L3))))
