filter([], []).
filter([H | T], S) :- H < 0, filter(T, S), !.
filter([H | T],[H | S]) :- filter(T, S).
