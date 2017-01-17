(clear)
(deffacts company
  (sotrudnik IvanovIvanIvanovich Engineering)
  (sotrudnik PetrovVasiliyFedorovich Accounting)
  (sotrudnik VasichkinEfstafiyBolzedorovich Administration))

(reset)
(facts)
(retract 1)
(retract 3)
(assert (sotrudnik MakarovPetrValeriyvich Engineering))

(facts)
