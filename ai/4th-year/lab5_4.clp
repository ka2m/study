(defrule sum
    =>
    (printout t "n=")
    (bind ?n (read))
    (bind ?l 1)
    (bind ?res 0)
    (while (<= ?l ?n) do
        (bind ?res (+ ?res (/ 1 (** (* 2 ?l) 2))))
        (bind ?l (+ 1 ?l)))
    (printout t "res= " ?res))
