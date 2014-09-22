(* return type: is (int * real) list *)

val x = 10;

let
  val A = x + 4
  val B = x + 5
  val C = x + 7
  val rA = real A
  val rB = real B
  val rC = real C
in
  [(B, rA/rC), (C, rB/rA), (A, rA/rC)]
end;

fun f x =
  let
    val A = x + 4
    val B = x + 5
    val C = x + 7
    val rA = real A
    val rB = real B
    val rC = real C
  in
    [(B, rA/rC), (C, rB/rA), (A, rA/rC)]
  end;
