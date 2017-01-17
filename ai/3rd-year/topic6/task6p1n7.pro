make_list(_, 0, _, []).
make_list(H, C, S, [H | T]) :- H1 is H + S
                             , C1 is C - 1
                             , make_list(H1, C1, S, T).

main :- prompt1('size: ')
      , read(N)
      , make_list(10, N, 5, L)
      , write(L).
