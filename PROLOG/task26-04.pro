llength([], 0).
llength([H | T], N) :- llength(T, N1), N is N1+1.

add(X, [], [X]).
add(X, [A|L], [A|L1]) :- add(X, L, L1).

insert(L, V, 0, [V|L]).
insert([H | T], V, N, R) :- Nn is N-1, insert(T, V, Nn, R0), R = [H | R0].

mytask(L, V, N, N, R).
mytask(L, V, N, _, R) :- llength(L, LL), N < LL, insert(L, V, N, R).
mytask(L, V, N, _, R) :- llength(L, LL), N >= LL, mytask(add(V, R, R1), V, N, LL, add(V, R, R1)).


task :- mytask([1,2], 3, 2, 0, R), write(R).
