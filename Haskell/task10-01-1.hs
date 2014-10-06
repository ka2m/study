derivation :: (Fractional a) => (a -> a) -> (a -> a)
derivation f = \ x -> ( ( f (x + dx) - f (x) ) / dx ) where dx = 0.1

evalA k f
  | k == 0 =  \x -> x
  | otherwise = \x -> (derivation (evalA (k-1) f) x) / (derivation f x)

inverseFun f x =
  let
    x0 = 3.0
    eps = 0.001
    iter k prev sum =
      let       
        elemA = evalA k f x0
        elemB = prev * (x - (f x0)) / (if k == 0 then 1 else k)
        newItem = elemA * elemB
      in
        if abs (newItem) < eps
        then sum
        else iter (k + 1) elemB (sum + newItem)
  in
    iter 0 1.0 0.0
    

f1 = \x -> 1.0 * x * x

main = do
  print $ inverseFun f1 2.5