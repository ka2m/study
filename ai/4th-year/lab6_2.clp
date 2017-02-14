(deffunction square (?a ?b ?c)
    (bind ?p (/ (+ ?a ?b ?c) 2))
    (sqrt (* ?p (- ?p ?a) (- ?p ?b) (- ?p ?c))))

(defrule compare
    =>
    (printout t "a1= ")
    (bind ?a1 (read))
    (printout t "b1= ")
    (bind ?b1 (read))
    (printout t "c1= ")
    (bind ?c1 (read))
    (printout t "a2= ")
    (bind ?a2 (read))
    (printout t "b2= ")
    (bind ?b2 (read))
    (printout t "c2= ")
    (bind ?c2 (read))
    (bind ?s1 (square ?a1 ?b1 ?c1))
    (bind ?s2 (square ?a2 ?b2 ?c2))
    (if (> ?s1 ?s2)
        then
        (printout t "s1 ( " ?s1 " ) > s2 ( " ?s2 " )" )
        else
        (printout t "s1 ( " ?s1 " ) < s2 ( " ?s2 " )" )))
