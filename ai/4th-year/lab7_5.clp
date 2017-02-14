(deffunction trimws (?str)
    (bind ?n (str-length ?str))
    (bind ?res "")
    (bind ?prev "")
    (loop-for-count (?i 1 ?n) do
        (bind ?c (sub-string ?i ?i ?str))
        (bind ?d (str-compare ?c " "))
        (bind ?dp (str-compare ?prev " "))
        (if (not (and (= ?d 0) (= ?dp 0)))
            then (bind ?res (str-cat ?res ?c)))
        (bind ?prev ?c))
    (printout t ?res crlf))


(defrule dorun
    =>
    (printout t "String = ")
    (bind ?str (readline))
    (trimws ?str))
