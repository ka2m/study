(deffunction firstrep (?str ?sym ?repl)
    (bind ?idx (str-index ?sym ?str))
    (if (eq ?idx FALSE)
        then ?str
        else  (str-cat (sub-string 1 (- ?idx 1) ?str)
                       ?repl
                       (sub-string (+ ?idx 1) (str-length ?str) ?str))))
(defrule dorun
   =>
   (printout t "String= ")
   (bind ?str (readline))
   (printout t "Orig sym= ")
   (bind ?sym (readline))
   (printout t "Replace sym= ")
   (bind ?repl (readline))
   (printout t (firstrep ?str ?sym ?repl) crlf))
