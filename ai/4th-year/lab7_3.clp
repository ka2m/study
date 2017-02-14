(deffunction removesubs (?str ?sub)
    (bind ?l (str-length ?sub))
    (bind ?f (str-index ?sub ?str))
    (while (not (eq ?f FALSE))
         (bind ?str (str-cat (sub-string 1 (- ?f 1) ?str)
                             (sub-string (+ ?f ?l) (str-length ?str) ?str)))
         (bind ?f (str-index ?sub ?str)))
    (printout t ?str))
(defrule dorun
    =>
    (printout t "String = ")
    (bind ?str (readline))
    (printout t "Substring = ")
    (bind ?sub (readline))
    (removesubs ?str ?sub))

