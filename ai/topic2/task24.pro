
рейс('А100',   'Москва',        14, 45, 'ежедн').
рейс('KLM23',  'Амстердам',     13, 10, 'чет').
рейс('S712 ',  'Токио',         18, 55, 'чет').
рейс('Y404',   'Торонто',       10, 20, 'ежедн').
рейс('KLM14',  'Амстердам',     22, 10, 'нечет').
рейс('LU545',  'Мюнхер' ,       15, 30, 'ежедн').
рейс('LU512',  'Берлин',        9,  50, 'нечет').
рейс('US1',    'Сан-Франциско', 11, 15, 'чет').
рейс('S765',   'Токио',         16, 55, 'чет').
рейс('UK123',  'Лондон',        12, 10, 'нечет').
рейс('NRW54',  'Хельсенки',     6, 50,  'ежедн').


t1 :- рейс(A, B, C, D, E), write(A/B/C:D/E), nl.

t2(X) :- рейс(A, X, C, D, E), E='чет',  write(A/X/C:D/E), nl.

t3(X, Y) :- рейс(A, B, C, D, E), E='ежедн', C*60+D =< X*60+Y, write(A/B/C:D/E), nl, false.
