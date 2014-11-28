add(X, [], [X]) :- !.
add(X, [A|L], [A|L1]) :- add(X, L, L1).

task(_, RP, -1, [], RL, RL) :- !.
task(_, RP, -1, [H | T], L, RL) :- RR is [L | H], task(V, RP, -1, T, RR, RL).
task(V, RP, RP, IL, L, RL) :- add(V, L, RR), task(V, RP, -1, IL, RR, RL).
task(V, RP, CP, [H | T], L, RL) :- NP is CP + 1, RR is [L | H], task(V, RP, NP, T, RR, RL).

calltask(V, P, L) :- task(V, P, 0, L, [], R), write(R), !.
