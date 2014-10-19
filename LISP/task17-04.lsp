(print
  (let ( (L1 '(T (U U1 U2) (U4 U6 U8)))
         (L2 '(4 6 (7 8 9)))
         (L3 '(78 89 90 67 45)))
    (list
      (cadr L1) ; second element from L1
      (caddr L2) ; third element from L2
      (cadddr L3)))) ; fourth element from L3
