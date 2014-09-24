cuttingSum :: Num a => [a] -> a -> [a]
cuttingSum [] _       = []
cuttingSum [x] _      = [x]
-- here goes list concatenation instead of append an item
cuttingSum (x:xs) sum  = [sum] ++ (cuttingSum xs (sum-x))
 

main = do
  -- used same thing twice as neither GHCi, nor Hugs
  -- allow using variables in interpretation mode  
  print $ cuttingSum [1,2,3] (foldl (+) 0 [1,2,3])