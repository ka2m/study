cuttingSum :: Num a => [a] -> [a]
cuttingSum l =
  let
    cuttingSum_iter [] _ res = reverse (res)
    cuttingSum_iter (x : xs) fs res =
      cuttingSum_iter xs (fs - x) (fs : res)
  in
    cuttingSum_iter l (foldl (+) 0 l) []


main = do
  print $ cuttingSum [1,2,3]