(deffunction isgreater (?a ?b)
    (> ?a ?b))

(defrule ask
    =>
    (printout t "Question: Is A greater than B? " crlf)
    (printout t "A= ")
    (bind ?a (read))
    (printout t "B= ")
    (bind ?b (read))
    (printout t (isgreater ?a ?b)) crlf)
