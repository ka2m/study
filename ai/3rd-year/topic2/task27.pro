запись('Анна', 8927).
запись('Борис', 5941).
запись('Василий', 1072).
запись('Григорий', 3122).
запись('Дмитрий', 8932).
запись('Елена', 8562).
запись('Женя', 2222).
запись('Зоя', 2722).
запись('Иван', 8902).
запись('Леонид', 7633).

t1 :- запись(X, Y), write(X:Y), nl, false.
t2(X) :- запись(X, Y), write(Y), nl.
t3(Y) :- запись(X, Y), write(X), nl.