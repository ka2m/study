int_mult(C, N,N,R,R) :- !.
int_mult(C, N,Nt,R,Rt):- N1 is Nt+1,R1 is Rt*(C/(log(Nt))), int_mult(C,N,N1,R,R1).

ext_mult(N, N, R, R):- !.
ext_mult(N, Nt, R, Rt) :- N1 is Nt+1, R1 is Rt*(int_mult(Nt, N, 2, RR, 1)), 
  ext_mult(N,N1,R,R1).

y(N) :- ext_mult((N+1), 1, R, 1).



