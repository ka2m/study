имя('Белокуров').
имя('Рыжов').
имя('Чернов').

цвет('блондин').
цвет('рыжый').
цвет('брюнет').

соотв(X, Y) :- имя(X)
             , цвет(Y)
             , ( X = 'Белокуров', not(Y = 'брюнет'), not(Y = 'блондин')
               ; X = 'Чернов', not(Y = 'брюнет')
               ; X = 'Рыжов', not(Y = 'рыжый')).

решение(X1, X2, X3, Y1, Y2, Y3) :- соотв(X1, Y1)
                                 , соотв(X2, Y2)
                                 , соотв(X3, Y3)
                                 , Y1 \= Y2
                                 , Y2 \= Y3
                                 , Y3 \= Y1.

main :- X1 = 'Белокуров'
      , X2 = 'Чернов'
      , X3 = 'Рыжов'
      , решение(X1, X2, X3, Y1, Y2, Y3)
      , format( "~s \t ~s~n~s \t\t ~s~n~s \t\t ~s~n"
              , [X1, Y1, X2, Y2, X3, Y3]).