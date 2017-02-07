(defrule nod
    =>
    (printout t "n= ")
    (bind ?n (read))
    (printout t "m= ")
    (bind ?m (read))
    (while (<> ?n ?m)
        (bind ?dif (abs (- ?n ?m)))
        (if (> ?n ?m) then
            (bind ?n ?dif)
            else (bind ?m ?dif)))
    (printout t "res= " ?n))
