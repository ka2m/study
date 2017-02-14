(deffunction rotate (?str ?res)
    (bind ?l (str-length ?str))
    (if (= ?l 0)
        then ?res
        else (rotate (sub-string 1 (- ?l 1) ?str)
                     (str-cat ?res (sub-string ?l ?l ?str)))))
(defrule dorun
    =>
    (printout t "String = ")
    (bind ?str (readline))
    (printout t (rotate ?str "") crlf))

