member(X, [X | _]).
member(X, [_ | T]) :- member(X, T).

substraction([], _, R) :- write(R), !.
substraction([H | T], [H | U], R) :- member(H, [H | U]), substraction(T, U, R).
substraction([H | T], [_ | U], R) :- substraction(T, U, [H | R]).

main :- R = [],  substraction([1,2,3,4], [4,2,5,6], R).
