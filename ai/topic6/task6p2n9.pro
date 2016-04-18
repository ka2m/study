list_size([], 0).
list_size([_ | T], R) :- list_size(T, R1), R is R1 + 1.


append([], L, L).
append([H | T], L2, [H | L3]) :- append(T, L2, L3).


list_div(L1, L2, L3) :- append(L2, L3, L1)
                      , list_size(L2, N1)
                      , list_size(L3, N2)
                      , N1 - N2 < 2
                      , N1 - N2 > -2.
