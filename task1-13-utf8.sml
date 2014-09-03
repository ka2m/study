(* return type: is (int * real) list *)

val x = 10;

let
  (* define function to return last element of the list *)
  fun last []   = raise Empty
  | last [x]    = x
  | last (h::t) = last t;
  
  (* list of x + N, where N are addedeniums 4, 5 and 7 *)
  val addedeniums = [4, 5, 7]   
  (* evaluate x + N and cast them for division *)
  val A = x + hd addedeniums
  val B = x + hd (tl addedeniums)
  val C = x + last addedeniums
  val rA = real A
  val rB = real B
  val rC = real C
in
  [(B, rA/rC), (C, rB/rA), (A, rA/rC)]
end;

fun f x =
  let    
    fun last []   = raise Empty
    | last [x]    = x
    | last (h::t) = last t;
        
    val addedeniums = [4, 5, 7]   
    val A = x + hd addedeniums
    val B = x + hd (tl addedeniums)
    val C = x + last addedeniums
    val rA = real A
    val rB = real B
    val rC = real C
  in
    [(B, rA/rC), (C, rB/rA), (A, rA/rC)]
  end;
