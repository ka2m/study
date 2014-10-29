(defun count-sublists (list)
  (labels
    ((iter (current other count level res)
      (if (null current)
        (if (null other)
          (cons (list level count) res)
          (iter other () 0 (1+ level) (cons (list level count) res)))
        (let ((myhead (car current)) (mytail (cdr current)))
          (if (listp myhead)
            (iter mytail other (1+ count) level res)
            (iter mytail (append (list myhead) other) count level res))))))
        (iter list () 0 1 ())))

(print (count-sublists '(A (B) C)))
