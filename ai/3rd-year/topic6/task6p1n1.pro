remove(X, [X|Y], Y).
remove(X, [A|C], [A|D]) :- remove(X, C, D).

main :- remove( 'Fri'
              , ['Mon', 'Tue', 'Wen', 'Thu', 'Fri', 'Sat', 'Sun']
              , R),
        write(R).
