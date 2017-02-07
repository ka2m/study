(deffacts company
    (sotrudnik Petrov 5 0 4000)
    (sotrudnik Sidorov 21 3 12000)
    (sotrudnik Popov 2 3 3500)
    (sotrudnik Markov 6 0 5000))
(defrule addBonus
    (sotrudnik ?name ?year ?children ?money)
    (test (or (>= ?year 5) (> ?children 2)))
    =>
    (assert (premia ?name (* (/ ?money 100) 20))))

(defrule allHaveBonuses
    (forall (sotrudnik ?name ?year ?children ?money)
    (premia ?name ?bonus))
    =>
    (printout t "All have bonuses" crlf))

(defrule veterans
    (sotrudnik ?name ?y ?c ?m)
    (test (> ?y 20))
    =>
    (printout t "Veterans found: " ?name crlf))

