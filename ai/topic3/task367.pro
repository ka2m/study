max(A, B, C) :- A > B
              , A > C
              , write(A).
max(A, B, C) :- A > B
              , write(C).
max(_, B, C) :- B > C
              , write(B).
max(_, _, C) :- write(C).

min(A, B, C) :- A < B
              , A < C
              , write(A).
min(A, B, C) :- A < B
              , write(C).
min(_, B, C) :- B < C
              , write(B).
min(_, _, C) :- write(C).
