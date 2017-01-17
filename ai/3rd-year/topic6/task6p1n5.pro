make_list(_, 0, _, []).
make_list(H, C, S, [H | T]) :- H1 is H + S
                             , C1 is C - 1
                             , make_list(H1, C1, S, T).

merge([], L, L).
merge([H | T], L2, [H | L3]) :- merge(T, L2, L3).

main :-  make_list(1, 5, 2, L1)
      ,  make_list(2, 5, 2, L2)
      ,  append(L1, L2, L3)
      ,  write(L3).

