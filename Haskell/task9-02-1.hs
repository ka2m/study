cuttingSum :: Num a => [a] -> [a]
cuttingSum l = 
  let         
    cuttingSum_iter [] res = reverse (res)
    cuttingSum_iter ll res =
      cuttingSum_iter (tail ll) ((foldl (+) 0 ll) : res)
  in
    cuttingSum_iter l []


main = do
  print $ cuttingSum [1,2,3]