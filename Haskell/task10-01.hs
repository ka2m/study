derivation :: Fractional a => (a -> a) -> (a -> a)
derivation f = 
  \ x -> (- f (x + 2 * dx) 
          + 8 * f (x + dx) 
          - 8 * f (x - dx) 
          + f (x - 2 * dx)) / (12 * dx)
            where dx = 0.1


inverseFun :: (Ord a, Fractional a) => (a -> a) -> a -> a
inverseFun f x = iter 0 1.0 0.0 (\x -> x)
    where
        x0 = 3.0
        eps = 0.001
        evalA' prev k = 
            if k == 0
            then \x -> x
            else \x -> ( derivation prev x / derivation f x )

        iter k prev sum' elemA =
            let elemB = prev * (x - f x0) / 
                        fromIntegral (if k == 0 then 1 :: Int else k)
                newf = evalA' elemA k
                newItem = newf x0 * elemB
            in  
                if abs newItem < eps
                then sum'
                else iter (k + 1) elemB (sum' + newItem) newf


f1 x = 1.0 * sqrt(x)

main = do
    print $ (inverseFun f1 2.5)