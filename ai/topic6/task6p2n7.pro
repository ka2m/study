ireverse([], L, L).
ireverse([H | T], L, R):- ireverse(T, [H | L] ,R).

list_reverse(L, R) :- ireverse(L, [], R).

main :- list_reverse([1,2,3,4,5], R), write(R).

