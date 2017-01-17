(clear)
(deffacts poezda
  (poezd a10 Moscow 1450)
  (poezd a20 Spb 1830)
  (poezd b10 Sochi 1200)
  )
(reset)
(assert (poezd a8 Rostov 1410))
(assert (poezd b2 Novgorod 1310))
(facts)

(retract 1 4)

(retract 2 3)

(assert (poezd a20 Spb 2030))
(assert (poezd b10 Sochi 1400))

(facts)
