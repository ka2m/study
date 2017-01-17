filter([], []).
filter([H | T], S) :- H  < 0, filter(T, S).
filter([H | T], [H | S]) :- H >= 0, filter(T, S).

main :- filter([1, 2, 3, -1, 5, -6, 2, -3], R), write(R).
