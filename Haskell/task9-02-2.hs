cuttingSum :: Num a => [a] -> [a]
cuttingSum []        = []
cuttingSum [x]       = [x]
-- here goes list concatenation instead of append an item
cuttingSum l@(x:xs)  = [(foldl (+) 0 l)] ++ cuttingSum xs

main = do
  print $ cuttingSum [1,2,3]