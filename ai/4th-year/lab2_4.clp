(clear)
(deffacts storage
   (tovar TV China 500 2)
   (tovar PS Korea 350 5)
   (tovar Headphones Japan 100 3))

(reset)
(facts)

(assert (tovar UHD-TV China 800 1))
(assert (tovar Pi UK 15 5))

(facts)

(retract 2 4)
(assert (tovar PS Korea 300 5))
(assert (tovar UHD-TV China 600 1))

(facts)
(clear)
(facts)
