make_list(_, 0, _, []).
make_list(H, C, S, [H | T]) :- H1 is H + S
                             , C1 is C - 1
                             , make_list(H1, C1, S, T).

sum([],0).
sum([X|Y], Res) :- sum(Y,Sum1), Res is X + Sum1.

main :- prompt1('size: ')
      , read(N)
      , make_list(10, N, 1, L)
      , sum(L, R)
      , write(R).
