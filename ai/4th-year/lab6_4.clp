(deffunction funcval (?x ?a)
    (if (= ?x 0)
        then 0
        else
        (if (< ?x 0)
        then (/ (abs (- ?x ?a)) (* ?x ?x))
        else (sin (abs (+ ?x ?a))))))

(defrule compute
    =>
    (printout t "x= ")
    (bind ?x (read))
    (printout t "a= ")
    (bind ?a (read))
    (printout t "Y= " (funcval ?x ?a)))
