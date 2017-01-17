(clear)
(deffacts students
   (student stud1 1)
   (student stud2 2)
   (student stud3 3)
   (student stud4 4))

(reset)
(facts)

(retract 2)
(facts)
(retract 3)
(assert (student stud3 4))
(facts)
