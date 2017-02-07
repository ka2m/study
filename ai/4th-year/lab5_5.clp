(defrule checkbalance
    =>
    (printout t "s0 = ")
    (bind ?s0 (read))
    (printout t "% = ")
    (bind ?yp (read))
    (bind ?toty 0)
    (bind ?aim (* 2 ?s0))
    (while (< ?s0 ?aim)
        (bind ?s0 (+ ?s0 (* (/ ?s0 100) ?yp)))
        (bind ?toty (+ 1 ?toty)))
    (printout t "years = " ?toty))

