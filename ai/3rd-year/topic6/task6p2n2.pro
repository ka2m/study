list_size([], 0).
list_size([_ | T], R) :- list_size(T, R1), R is R1 + 1.

main :- list_size([1, 2, 3, 4, 5], R), write(R).
