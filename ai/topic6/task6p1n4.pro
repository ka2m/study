make_list(_, 0, _, []).
make_list(H, C, S, [H | T]) :- H1 is H + S
                             , C1 is C - 1
                             , make_list(H1, C1, S, T).

remove(X, [X|Y], Y).
remove(X, [A|B], [A|D]) :- remove(X, B, D).


wrap(I, L, L1) :- remove(I, L, L1), write(L1), !.
wrap(I, L, L1) :- write(L).

main :- make_list(2, 5, 2, L)
      , prompt1('item: ')
      , read(I)
      , wrap(I, L, L1).
