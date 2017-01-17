sum([],0).
sum([X|Y], Res) :- sum(Y,Sum1), Res is X + Sum1.

main :- sum([1, 2, 3, 4], X), write(X).
