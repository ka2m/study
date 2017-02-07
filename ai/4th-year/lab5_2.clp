(defrule spisok_sotr
    =>
    (printout t "n=")
    (bind ?n (read))
    (loop-for-count ?n do
        (printout t "FIO:" )
        (bind ?name (readline))
        (printout t "Dolzhnost:" )
        (bind ?pos (readline))
        (assert (sotrudnik ?name ?pos))))
