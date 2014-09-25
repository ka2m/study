cuttingSumWrapper :: Num a => [a] -> [a]
cuttingSumWrapper l =
  let     
    cuttingSum [] _       = []
    cuttingSum [x] _      = [x]
    -- here goes list concatenation instead of append an item
    cuttingSum (x:xs) sum  = [sum] ++ (cuttingSum xs (sum-x))
  in
    cuttingSum l (foldl (+) 0 l)
 

main = do
  print $ cuttingSumWrapper [1,2,3] 