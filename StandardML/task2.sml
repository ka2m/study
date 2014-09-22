(* program uses one-numeration: fib 0 returns 0 *)

fun fib n =
  let fun fibIter a b count =
    if count = 0 then b 
    else fibIter (a + b) a (count - 1)
  in
    fibIter 1 0 n
  end
