(deffunction sum (?n ?res)
    (if (= ?n 1)
        then (+ ?res 1)
        else (sum (- ?n 1) (+ ?res (/ 1 (* ?n ?n))))))

(defrule runsum
    =>
    (printout t "n= ")
    (bind ?n (read))
    (printout t "S= " (sum ?n 0)))
