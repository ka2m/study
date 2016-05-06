initial_state([1,1,1,1,1,1,1]).
final_state([2,2,2,2,2,2,2]).

next_state(S,S1) :- move(S,S1), not(unsafe(S1)).
% [D1,D2,D3,G1,G2,G3, S]
% move([D1,D2,D3,G1,G2,G3,F], [D1,D2,D3,G1,G2,G3,F1]) :- cross(F,F1).  шаблон
move([F,D2,D3,G1,G2,G3,F], [F1,D2,D3,G1,G2,G3,F1]) :- cross(F,F1).  % отец 1 поплыл один
move([D1,F,D3,G1,G2,G3,F], [D1,F1,D3,G1,G2,G3,F1]) :- cross(F,F1).  % отец 2 поплыл один
move([D1,D2,F,G1,G2,G3,F], [D1,D2,F1,G1,G2,G3,F1]) :- cross(F,F1).  % отец 3 поплыл один

move([D1,D2,D3,F,G2,G3,F], [D1,D2,D3,F1,G2,G3,F1]) :- cross(F,F1).  % дочь 1 поплыла один
move([D1,D2,D3,G1,F,G3,F], [D1,D2,D3,G1,F1,G3,F1]) :- cross(F,F1).  % дочь 2 поплыла один
move([D1,D2,D3,G1,G2,F,F], [D1,D2,D3,G1,G2,F1,F1]) :- cross(F,F1).  % дочь 3 поплыла один

move([F,F,D3,G1,G2,G3,F], [F1,F1,D3,G1,G2,G3,F1]) :- cross(F,F1).  % отец 1 и отец 2 поплыли в лодке
move([F,D2,F,G1,G2,G3,F], [F1,D2,F1,G1,G2,G3,F1]) :- cross(F,F1).  % отец 1 и отец 3 поплыли в лодке
move([D1,F,F,G1,G2,G3,F], [D1,F1,F1,G1,G2,G3,F1]) :- cross(F,F1).  % отец 2 и отец 3 поплыли в лодке

move([F,D2,D3,F,G2,G3,F], [F1,D2,D3,F1,G2,G3,F1]) :- cross(F,F1).  % отец 1 и дочь 1 поплыли в лодке
move([D1,F,D3,G1,F,G3,F], [D1,F1,D3,G1,F1,G3,F1]) :- cross(F,F1).  % отец 2 и дочь 2 поплыли в лодке
move([D1,D2,F,G1,G2,F,F], [D1,D2,F1,G1,G2,F1,F1]) :- cross(F,F1).  % отец 3 и дочь 3 поплыли в лодке

move([D1,D2,D3,F,F,G3,F], [D1,D2,D3,F1,F1,G3,F1]) :- cross(F,F1). % дочь 1 и дочь 2 поплыли в лодке
move([D1,D2,D3,F,G2,F,F], [D1,D2,D3,F1,G2,F1,F1]) :- cross(F,F1). % дочь 1 и дочь 3 поплыли в лодке
move([D1,D2,D3,G1,F,F,F], [D1,D2,D3,G1,F1,F1,F1]) :- cross(F,F1). % дочь 2 и дочь 3 поплыли в лодке

% Небезопасные состояния
% Небезопасные состояния
unsafe([X,Y,_,Y,_,_,_]) :- not(X=Y).  % Когда 1 дочь осталась с 2 рыцарем
unsafe([X,_,Y,Y,_,_,_]) :- not(X=Y).  % Когда 1 дочь осталась с 3 рыцарем
unsafe([Y,X,_,_,Y,_,_]) :- not(X=Y).  % Когда 2 дочь осталась с 1 рыцарем
unsafe([_,X,Y,_,Y,_,_]) :- not(X=Y).  % Когда 2 дочь осталась с 3 рыцарем
unsafe([Y,_,X,_,_,Y,_]) :- not(X=Y).  % Когда 3 дочь осталась с 1 рыцарем
unsafe([_,Y,X,_,_,Y,_]) :- not(X=Y).  % Когда 3 дочь осталась с 2 рыцарем

% Переход на другую сторону
cross(1,2).
cross(2,1).

% Поиск в глубину
dfs(AnsPath) :- initial_state(Init)
              , d_iter([Init], AnsPath).

d_iter([S|Path], [S]) :- final_state(S), !.
d_iter([S|Path], [S|AnsPath]) :- write('Current path: '), write([S|Path]), nl
                               , extend([S|Path], S1)
                               , write('Next step: '), write(S1), nl
                               , d_iter([S1,S|Path], AnsPath).


extend([S|Path], S1) :- next_state(S,S1)
                      , not(member(S1, [S|Path])).

member(S, [S|_]).
member(X, [_|T]) :- member(X,T).

main :-dfs(AnsPath).
