(print
  (let ((L1 '(9 (() 8 88 888)))
        (L2 '(H (J K L) (UJN)))
        (L3 '(C B (N M I) (T Y U))))
    (append
      (list (car L1)) ; take only first element of L1 - 9
      (list (car L2)  ; take first and second elemnts of L2 - H
            (cadr L2)) ; and (J K L)
      (list (car L3) ; take first three elements of L3 - C
            (cadr L3) ; B
            (cadddr L3))))) ; (T Y U)
