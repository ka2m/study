primedivisors :: [[Int]]
primedivisors = map divs [1 ..]
  where    
    -- Generate infinite list of prime numbers
    primes = sieve [2..]
    sieve (p : xs) = p : sieve [x | x <- xs, x `mod` p > 0]
    -- Append only matching divisors and 1. Map is better
    -- as sieve in primes is using recursion
    divs x =  1 : [y | y <- take x primes, x `rem` y == 0] 

main = do
  print $ take 4 primedivisors
  print $ take 6 primedivisors
