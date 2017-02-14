(deffunction repl (?str)
    (bind ?res "")
    (loop-for-count (?i 1 (str-length ?str)) do
        (bind ?c (sub-string ?i ?i ?str))
        (bind ?d (str-compare ?c " "))
        (bind ?res
            (str-cat ?res (if (= ?d 0) then "_" else ?c))))
    (printout t ?res crlf))

(defrule dorun
    =>
    (printout t "String= ")
    (bind ?str (readline))
    (repl ?str))
