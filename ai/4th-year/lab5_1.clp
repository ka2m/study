(defrule zachisl
    =>
    (printout t "n=")
    (bind ?n (read))
    (loop-for-count ?n do
        (printout t "FIO:" )
        (bind ?name (readline))
        (assert (student ?name 1))))
