t1(X) :- X \= 2, Y=(X * X + 1)/(X - 2),
         format("Y=~f~n", [Y]);
         format("Divided by zero~n", []).

t2(X, Y) :- X \= Y, S=(X * X + Y * Y)/(X - Y),
         format("S=~f~n", [S]);
         format("Divided by zero~n", []).

t3(X, Y) :- format("Avg=~f~n", [(X + Y) /2]).

t4(X) :- Z = (X mod 2), Z =:= 0,
         format("Even~n", []);
         format("Odd~n", []).

t5(X, A, B) :- X >= A, X =< B,
               format("In~n", []);
               format("Out~n", []).

