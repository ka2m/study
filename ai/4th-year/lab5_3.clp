(defrule factorial
    =>
    (printout t "n=")
    (bind ?n (read))
    (bind ?res 1)
    (while (> ?n 0) do
        (bind ?res (* ?res ?n))
        (bind ?n (- ?n 1)))
    (printout t "res= " ?res))
