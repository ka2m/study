fun y N =
  let
    val rN = real N

    (* evaluate each term of series *)
    fun evalTerm (i, j) = i - j * j * j

    (* internal product of term *)
    fun jIter (i, j, term) =
      if j > rN then term
      else jIter (i, j + 1.0, term * evalTerm (i, j))

    (* external sum of product *)
    fun iIter (i, res) =
      if i > rN then res
      else iIter (i + 1.0, res + jIter (i, 1.0, 1.0))
  in
    iIter (1.0, 0.0)
  end;
