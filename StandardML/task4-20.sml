fun y N =
  let
    val rN = real N

    (* evaluate each term of series *)
    fun evalTerm (i, j) = i - j * j * j

    (* loop via two nested interators
     * i - external loop - sum 1..N  
     * j - internal loop - prod 1..N of term
     * product - current internal loop value
     * sum - current external loop value *)
    fun iter (i, j, product, sum) =
      if i > rN      then sum
      else if j > rN then iter (i + 1.0, 1.0, 1.0, product + sum)
      else iter (i, j + 1.0, product * evalTerm (i, j), sum)

  in
    (* iterate over sum of product of defined term 
     * from 1..N in each case *)
    iter (1.0, 1.0, 1.0, 0.0)
  end;
