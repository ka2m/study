member(X, [X | _]).
member(X, [_ | T]) :- member(X, T).

intersection([H | T], L, [H | U]) :- member(H, L), intersection(T,L , U).
intersection([_ | T], L, U) :- intersection(T, L, U).
intersection(_, _, []).

main :- intersection([1,2,3,4], [4,2,5,6], R), write(R).
