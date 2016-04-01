prod([], 1).
prod([X|Y], Res) :- prod(Y, P1), Res is X * P1.

main :- prod([1, 2, 3, 4, 5], R), write(R).

