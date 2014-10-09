derivation :: (Fractional a) => (a -> a) -> a -> a
derivation f = \ x -> ( f (x + dx) - f x ) / dx where dx = 0.1

evalA :: (Fractional a) => Int -> (a -> a) -> a -> a
evalA k f = iterate (\prev x -> derivation prev x / derivation f x) id !! k

inverseFun :: (Ord a, Fractional a) => (a -> a) -> a -> a
inverseFun f x = iter 0 1.0 0.0
    where
        x0 = 3.0
        eps = 0.001
        iter k prev sum' =
            let elemB = prev * (x - f x0) / 
                        fromIntegral (if k == 0 then 1 :: Int else k)
                newItem = evalA k f x0 * elemB
            in  if abs newItem < eps
                    then sum'
                    else iter (k + 1) elemB (sum' + newItem)


f1 x = 1.0 * sqrt(x)

main = do
    print $ (inverseFun f1 2.5)