list_sort([], []).
list_sort([H|T], R) :- list_sort(T, L), insertInPlace(H, L, R).


insertInPlace(X, [], [X]).

insertInPlace(X, [H | T], [X | L]) :- X =< H, insertInPlace(H, T, L), !.

insertInPlace(X, [H | T], [H | L]) :- insertInPlace(X, T, L).


main :- list_sort([10, 5, -1, 3, 4, 17, 2], R), write(R).
