list_size([], 0).
list_size([_ | T], R) :- list_size(T, R1), R is R1 + 1.


insert(H, L, 0, [H | L]).
insert(I, [H | T], P, [H | T1]) :- P > 0
                                 , P1 is P - 1
                                 , insert(I, T, P1, T1).

task(_, _, -1) :- !.
task(I, L, C) :- insert(I, L, C, NL)
               , write(NL)
               , write('\n')
               , C1 is C - 1
               , task(I, L, C1).

wrap(I, L) :- list_size(L, S), task(I, L, S).

main :- prompt1("item: ")
      , read(I)
      , wrap(I, [1,2,3,4,5]).
