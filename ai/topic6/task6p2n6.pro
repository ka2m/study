intersection([], _, []).
intersection([H1 | T1], L2, [H1 | Res]) :- member(H1, L2)
                                         , intersection(T1, L2, Res).
intersection([_ | T1], L2, Res) :- intersection(T1, L2, Res).


main :- intersection([1,2,3,4], [4,1,2], R), write(R).
