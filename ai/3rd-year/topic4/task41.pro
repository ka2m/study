power_w(N, 0, 1):- !.
power_w(N, C, R):- C1 is C-1
                 , power_w(N,C1,R1)
                 , R is R1*N.

power(X, Y) :- power_w(X, Y, R), write(R), nl.
