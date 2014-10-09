derivation :: Fractional a => (a -> a) -> (a -> a)
derivation f = 
  \ x -> (- f (x + 2 * dx) 
          + 8 * f (x + dx) 
          - 8 * f (x - dx) 
          + f (x - 2 * dx)) / (12 * dx)
            where dx = 0.1


inverseFun :: (Ord a, Fractional a) => (a -> a) -> a -> a
inverseFun f x = iter 0 0.0 (\x -> x) 0.0 1.0
    where
        x0 = 3.0
        eps = 0.001
        elemB = x - f x0
        
        -- get new A_k
        evalA prev k 
            | k == 0    = \x -> x
            | otherwise = \x -> ( derivation prev x / derivation f x )
            
        -- get new (x - F(x_0))^k
        evalB b k 
            | k == 0    = 1.0
            | k == 1    = elemB
            | otherwise = b * elemB

        iter k sum' prevA prevB prevBdenom =
            let 
                newB = evalB prevB k                
                -- newB/k!
                newBdenom = if k == 0 then 1.0 else prevBdenom*k
                
                newA = evalA prevA k                
                
                newItem = ( newA x0 ) * newB / newBdenom
            in  
                if abs newItem < eps
                then sum'
                else iter (k + 1) (sum' + newItem) newA newB newBdenom 


f1 x = 1.0 * sqrt(x)

main = do
    print $ (inverseFun f1 2.5)