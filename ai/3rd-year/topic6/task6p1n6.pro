make_list(_, 0, _, []).
make_list(H, C, S, [H | T]) :- H1 is H + S
                             , C1 is C - 1
                             , make_list(H1, C1, S, T).

insert(H, L, 0, [H | L]).
insert(I, [H | T], P, [H | T1]) :- P > 0
                                 , P1 is P - 1
                                 , insert(I, T, P1, T1).

main :- prompt1('item: ')
      , read(I)
      , prompt1('position: ')
      , read(P)
      , make_list(3, 6, 3, L)
      , insert(I, L, P, L1)
      , write(L1).
