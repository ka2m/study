out(X, Y) :- write('Перенести диск с ')
             , write(X)
             , write(' на ')
             , write(Y)
             , nl.

hanoi(0, _, _, _) :- !.
hanoi(N, A, B, C) :- M is N-1
                   , hanoi(M, A, C, B)
                   , out(A, B)
                   , hanoi(M, C, B, A).



main(N) :- hanoi(N, 'A', 'B', 'C').
