item_by_index([], _, _, _) :- !.
item_by_index([H|_], N, N, H).
item_by_index([_|T], N, M, A) :- N \= M
                               , N1 is N + 1
                               , item_by_index(T, N1, M, A).


index_wrap(L, I, A) :- item_by_index(L, 0, I, A).

collocate(_, [], _) :- !.
collocate(L1, [H | T], [H2]) :- index_wrap(L1, H, H2), collocate(L1, T, []).
collocate(L1, [H | T], [H2 | R]) :- index_wrap(L1, H, H2), collocate(L1, T, R).

main :-
    collocate(['Zero', 'One', 'Two', 'Three', 'Four', 'Five', 'Six', 'Seven', 'Eight', 'Nine'],
              [2, 3, 0, 4, 7, 1, 6, 8, 5, 9], L),
    write(L).
