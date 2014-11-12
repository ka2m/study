(defmacro sum-range ((iter-var low-bound high-bound) &body body)
  (let ((iter (gensym)) (sum (gensym)))
    `(let ((,iter-var ,low-bound) (,sum 0))
       (labels ((,iter ()
                  (if (<= ,iter-var ,high-bound)
                      (progn (incf ,sum (progn ,@body))
                             (incf ,iter-var)
                             (,iter))
                      ,sum)))
                (,iter)))))

(defmacro prod-range ((iter-var low-bound high-bound) &body body)
  (let ((iter (gensym)) (prod (gensym)))
    `(let ((,iter-var ,low-bound) (,prod 1))
       (labels ((,iter ()
                  (if (<= ,iter-var ,high-bound)
                      (progn (setq ,prod (* ,prod (progn ,@body)))
                             (incf ,iter-var)
                             (,iter))
                      ,prod)))
                (,iter)))))

; task 20 variant 19
(defun y (N)
  (sum-range (i 1 N) (sum-range (j 1 N) (+ (sqrt i) (* j j)))))

(print (y 20))
