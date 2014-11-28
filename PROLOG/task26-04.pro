%% pushback to list
add(X, [], [X]) :- !.
add(X, [A | L], [A | L1]) :- add(X, L, L1).

%% get head
hh([H | _], H) :- !.

%% reverse list
rev([], A, A) :- !.
rev([H | T], A, R):- rev(T, [H | A], R). 

%% get the last element of the list
getLastElem(L, R):- rev(L,[], RR), hh(RR, P), R is P.
getLastElem([], R):- hh([0], P), R is P.

%% task(MyLastElem, Value, ResultingPosition, CurrentPositon, InitialList,
%%      ResultingList, ptr).
task(_, _, _, -1, [], RL, RL) :- !.

%% if InitialList is empty, and resulting position = currentposition,
%% append to list
task(_, V, RP, RP, [], L, RL) :- add(V, L, RR)
                               , task(_, V, RP, -1, [], RR, RL).

%% if InitialList is empty, but we didn't reach ResultingPosition
%% duplicate the last element
task(ML, V, RP, CP, [], L, RL) :- NP is CP + 1
                                , add(ML, L, RR)
                                , task(ML, V, RP, NP, [], RR, RL).

%% if ResultingPosition was reached, but we the InitialList is not empty
%% append the tail of InitialList to the ResultingList
task(_, _, RP, -1, [H | T], L, RL) :- add(H, L, RR)
                                    , task(_, _, RP, -1, T, RR, RL).

%% if ResultingPosition was reached, append this element to ResultingList
%% and switch to "add-tail" mode (CP = -1)
task(_, V, RP, RP, IL, L, RL) :- add(V, L, RR)
                               , task(_, V, RP, -1, IL, RR, RL).

%% if neither ResultingPosition reached, nor InitialList is empty, add 
%% head of InitialList to ResultingList
task(ML, V, RP, CP, [H | T], L, RL) :- NP is CP + 1
                                     , add(H, L, RR)
                                     , task(ML, V, RP, NP, T, RR, RL).

calltask(V, P, L) :- getLastElem(L, ML)
                   , task(ML, V, P, 0, L, [], R)
                   , writeln(R)
                   , !.

%% run test cases
main :- calltask(-1, 0, [])
      , calltask(-1, 1, [])
      , calltask(-1, 2, [])
      , calltask(-1, 0, [1])
      , calltask(-1, 1, [1])
      , calltask(-1, 2, [1])
      , calltask(-1, 0, [1, 2, 3])
      , calltask(-1, 1, [1, 2, 3])
      , calltask(-1, 3, [1, 2, 3])
      , calltask(-1, 4, [1, 2, 3])
      , calltask(-1, 5, [1, 2, 3]).