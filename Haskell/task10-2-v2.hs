derivation :: (Fractional a) => (a -> a) -> a -> a
derivation f = \ x -> ( f (x + dx) - f x ) / dx where dx = 0.1


evalA' :: (Fractional a) => (a -> a) -> (a -> a) -> (a -> a)
evalA' prev f = \x -> derivation prev x / derivation f x

inverseFun :: (Ord a, Fractional a) => (a -> a) -> a -> a
inverseFun f x = iter 0 1.0 0.0 (\x -> x)
    where
        x0 = 3.0
        eps = 0.001
        iter k prev sum' elemA =
            let elemB = prev * (x - f x0) / 
                        fromIntegral (if k == 0 then 1 :: Int else k)
                elemA = evalA' elemA f
                newItem = elemA x0 * elemB
            in  if abs newItem < eps
                    then sum'
                    else iter (k + 1) elemB (sum' + newItem) elemA


f1 x = 1.0 * x * x

main = do
    print $ (inverseFun f1 2.5)