isPrime' :: Integer -> Integer -> Bool
isPrime' x m 
  | (m > (floor . sqrt . fromInteger) x) = True 
  | otherwise = ((x `mod` m) /= 0) && (isPrime' x (m + 1))  
 
isPrime :: Integer -> Bool
isPrime x = isPrime' x 2

pl' :: Integer -> Integer -> [Integer] -> [Integer]
pl' n m x 
  | (head x) > n = tail x
  | otherwise = if (isPrime m) 
                then pl' n (m + 1) (m : x)
                else pl' n (m + 1) x 
 
pl :: Integer -> [Integer]
pl n = pl' n 3 [2]
                                 
divsl :: Integer -> [Integer]
divsl n = 1 : reverse ( filter (\x -> (n `mod` x) == 0) (pl n) )
                                 
primedivs' :: [Integer] -> [[Integer]]
primedivs' = map (\ x -> divsl x) 

primedivs :: [[Integer]]
primedivs = primedivs' [1..]

main = do
  print $ take 3 primedivs 
  print $ take 5 primedivs
  print $ take 10 primedivs