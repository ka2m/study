list_prod([], [], []).
list_prod([H1 | T1], [H2 |T2], [X |R]) :- list_prod(T1, T2, R)
                                        , X is H1 * H2.

main :- list_prod([1, 2, 3], [4, 5, 6], R), write(R).
