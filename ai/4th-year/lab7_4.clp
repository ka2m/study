(deffunction addstars (?str ?n)
    (if (= ?n 0)
        then ?str
        else (addstars (str-cat ?str "*") (- ?n 1))))
(deffunction check (?s1 ?s2)
    (bind ?l1 (str-length ?s1))
    (bind ?l2 (str-length ?s2))
    (bind ?diff (abs (- ?l1 ?l2)))
    (if (> ?l1 ?l2) then
        (printout t ?s1 crlf)
        (printout t (addstars ?s2 ?diff) crlf)
        else
        (printout t (addstars ?s1 ?diff) crlf)
        (printout t ?s2 crlf)
    ))

(defrule dorun
    =>
    (printout t "S1 = ")
    (bind ?s1 (readline))
    (printout t "S2 = ")
    (bind ?s2 (readline))
    (check ?s1 ?s2))
