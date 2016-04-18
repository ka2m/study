gt(X,Y,Y) :- X  =<  Y,!.
gt(X,Y,X) :- X>Y.

max_list([H], H).
max_list([H|T], M2) :- max_list(T, M), gt(H, M, M2).

main :- max_list([1, 10, 4, 4, 5], R), write(R).
