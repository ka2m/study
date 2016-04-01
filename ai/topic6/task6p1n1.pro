remove(X, [X|Y], Y).
remove(X, [A, B|C], [A|D]) :- remove(X, [B|C], D).

main :- remove( 'Fri'
              , ['Mon', 'Tue', 'Wen', 'Thu', 'Fri', 'Sat', 'Sun']
              , R),
        write(R).
