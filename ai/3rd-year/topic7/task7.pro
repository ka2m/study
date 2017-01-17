language("BCPL") :- it_is("strongly compiled")
                  , it_is("Proc")
                  , it_is("Struc")
                  , influenced_by("CPL").

language("C") :- it_is("strongly compiled")
               , it_is("tiobe")
               , it_is("Proc")
               , it_is("Struc")
               , influenced_by("BCPL")
               , influenced_by("Algol")
               , influenced_by("Fortran").

language("C++") :- it_is("strongly compiled")
                 , it_is("OO")
                 , it_is("Proc")
                 , it_is("tiobe")
                 , influenced_by("C")
                 , influenced_by("Algol").

language("Scheme") :- it_is("vm")
                    , it_is("Proc")
                    , it_is("Func")
                    , influenced_by("LISP")
                    , influenced_by("Algol").

language("Clojure") :- it_is("vm")
                     , it_is("Func")
                     , influenced_by("Haskell")
                     , influenced_by("Java")
                     , influenced_by("LISP").

language("SmallTalk") :- it_is("strongly compiled")
                       , it_is("OO")
                       , influenced_by("LISP").

language("Objective-C") :- it_is("strongly compiled")
          			 , it_is("OO")
                         , it_is("tiobe")
                         , influenced_by("SmallTalk")
                         , influenced_by("C").

language("SML") :- it_is("strongly compiled")
                , it_is("Func").

language("Caml") :- it_is("vm")
                  , it_is("Func")
                  , influenced_by("ML").

language("OCaml") :- it_is("vm")
       			, it_is("OO")
                   , it_is("Func")
                   , influenced_by("Caml").

language("bash") :- it_is("strongly interpreted")
                  , it_is("Shell")
                  , influenced_by("sh").

language("csh") :- it_is("strongly interpreted")
                 , it_is("Shell")
                 , influenced_by("C")
                 , influenced_by("bash").

language("sh") :- it_is("strongly interpreted")
                , it_is("Shell").


language("Groovy") :- it_is("vm")
                    , it_is("OO")
                    , it_is("tiobe")
                    , influenced_by("Java")
                    , influenced_by("SmallTalk")
                    , influenced_by("Objective-C")
                    , influenced_by("Python").

language("Haskell") :- it_is("vm")
                     , it_is("Func")
                     , influenced_by("SML")
                     , influenced_by("Scheme").

language("Scala") :- it_is("vm")
                   , it_is("OO")
                   , it_is("Func")
                   , influenced_by("Java")
                   , influenced_by("Smalltalk")
                   , influenced_by("SML")
                   , influenced_by("Scheme")
                   , influenced_by("OCaml").

language("Java") :- it_is("vm")
                  , it_is("OO")
                  , influenced_by("C++")
                  , influenced_by("Objective-C")
                  , influenced_by("Pascal").

language("JS") :- it_is("strongly interpreted")
                , it_is("OO")
                , it_is("tiobe")
                , influenced_by("Scheme")
                , influenced_by("Python")
                , influenced_by("C")
                , influenced_by("Java").

language("C#") :- it_is("vm")
                , it_is("OO")
                , influenced_by("C++")
                , influenced_by("Pascal").

language("Python") :- it_is("strongly interpreted")
                    , it_is("OO")
	               , it_is("Proc")
                    , it_is("Struc")
                    , it_is("tiobe")
                    , influenced_by("C++")
                    , influenced_by("C")
                    , influenced_by("Java")
                    , influenced_by("LISP")
                    , influenced_by("Haskell")
                    , influenced_by("Algol").

language("Fortran") :- it_is("strongly compiled")
                     , it_is("OO")
                     , it_is("Proc")
				  , it_is("Struc").

language("Algol") :- it_is("strongly compiled")
                   , it_is("Proc")
				, it_is("Struc")
                   , influenced_by("Fortran").

language("LISP") :- it_is("vm")
 			    , it_is("Func")
			    , it_is("Proc").

language("Pascal") :- it_is("strongly compiled")
                    , it_is("Struc")
                    , influenced_by("Algol").


it_is("strongly compiled") :- true_("can only be", "compiled").
it_is("strongly interpreted") :- true_("can only be", "interpreted").
it_is("vm") :- true_("has", "code VM").

it_is("OO") :- true_("is", "objective-oriented").
it_is("Func") :- true_("is", "functional").
it_is("Struc") :- true_("is", "structured").
it_is("Proc") :- true_("is", "procedural").
it_is("Shell") :- true_("used", "as shell").
it_is("tiobe") :- true_("still in", "TIOBE rating").

influenced_by(X) :- true_("influenced by", X).

true_(X, Y) :- xtrue_(X, Y), !.

true_(X, Y) :- not(xfalse_(X, Y)), ask(X, Y, Reply), Reply=yes.

false_(X, Y) :- xfalse_(X, Y), !.
false_(X, Y) :- not(xtrue_(X, Y)), ask(X, Y, Reply),Reply=no.
ask(X, Y, Reply) :- read(Reply, X+" "+Y), remember(X,Y,Reply).


remember(X, Y, yes) :- assert(xtrue_(X,Y)).
remember(X, Y, no) :- assert(xfalse_(X,Y)).

main :- language(X),!,
write("\n Language is "),write(X), clear_facts.
main :- write("\n Unfortunately, knowledge base it isn't enough "), clear_facts.

?-main.