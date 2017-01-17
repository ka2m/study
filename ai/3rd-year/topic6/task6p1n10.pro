make_list(_, 0, _, []).
make_list(H, C, S, [H | T]) :- H1 is H + S
                             , C1 is C - 1
                             , make_list(H1, C1, S, T).

prod([], 1).
prod([X|Y], Res) :- prod(Y, P1), Res is X * P1.

main :- make_list(7, 4, -2, L)
      , prod(L, R)
      , write(R).
