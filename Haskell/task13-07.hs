import Data.List

-- Classes definition

data Term = IT (Int, Double)

data Polynomial = Polynomial [Term]

-- Term accessors

power :: Term -> Int
power (IT (x, _)) = x

value :: Term -> Double
value (IT (_, x)) = x

-- Term instances

instance Ord Term where
  IT (x, _) <= IT (x', _) = x'<= x

instance Eq Term where
  IT (x, _) == IT (x', _) = x' == x

instance Num Term where
  IT (a, b) + IT (a', b')
    | a == a' = IT (a, b + b')
    | otherwise = error "Powers are not equal"

  IT (a, b) * IT (a', b') = IT (a + a', b * b')
  abs (IT (a, b)) = IT (a, abs b)
  signum (IT (_, b))
    | b > 1 = 1
    | b < 1 = -1
    | otherwise = 0

  negate (IT (a, b)) = IT (a, negate b)

instance Show Term where
  show (IT (x, y))
    | x == 0 && y /= 0 =  show y
    | x == 1 = show y ++ "x"
    | otherwise = show y ++ "x^" ++ show x

-- Helping functions

findTerm :: [Term] -> Term -> Term
findTerm [] y = IT (0, 0)
findTerm (x : xs) y
  | power x == power y = x
  | otherwise = findTerm xs y

-- Polynomial instances

instance Show Polynomial where
  show (Polynomial p) =
    let
      v = foldr (++) "" [ sign' x | x <- sort p] where
      sign' x
        | value x > 0 = "+" ++ show (abs x)
        | value x < 0 = "-" ++ show (abs x)
        | otherwise = ""
    in
      if value (head p) > 0
      then tail v
      else if v == "" then "0.0" else v

instance Eq Polynomial where
  Polynomial a == Polynomial a' =  a == a' && vall a == vall a' where
    vall p = [x | IT (_, x) <- p]

instance Num Polynomial where
  Polynomial a + Polynomial a' =
    Polynomial (sort ((a \\ a') ++ (a' \\ a) ++ (reduce a a')))
      where
        reduce p p' =
          let
            f' (p, _) = p
            s' (_, p) = p
            s [] res = reverse res
            s (x : xs) res = s xs
                               ( IT (power (f' x),
                                    value (f' x) + value (s' x)) : res)
          in
            s (zip (sort(intersectBy (\x y -> x == y) p p'))
                   (sort(intersectBy (\x y -> x == y) p' p)) ) []

  Polynomial a - Polynomial a' =
    Polynomial a + (negate (Polynomial a'))

  Polynomial a * Polynomial a' =
    Polynomial (multIter (terml (Polynomial a)) (terml (Polynomial a')) [])
      where
        multIter [] [] res = res
        multIter (x : xs) [] res = multIter xs (terml (Polynomial a')) res
        multIter (x : xs) (y : ys) res = multIter (x : xs) ys [x * y] ++ res
        multIter _ _ res = res

  abs (Polynomial a) = Polynomial [abs x | x <- a]
  negate (Polynomial a) = Polynomial [negate t | t <- a]

-- Helping functions

-- Unwrap
terml :: Polynomial -> [Term]
terml (Polynomial p) = p

a1 = IT (0, 1.0)
a2 = IT (1, -2.0)
a3 = IT (2, 3.0)
p = Polynomial [a1, a2, a3]

a0' = IT (4, 7.0)
a1' = IT (3, 4.0)
a2' = IT (2, 8.0)
p' = Polynomial [ a0', a1', a2']

main = do
  putStrLn "Check output of x^0:"
  print $ a1
  putStrLn "Check output of x^1:"
  print $ a2
  putStrLn "Check output of x^(>= 2):"
  print $ a3
  putStrLn "Check the whole polynomial print:"
  print $ p
  putStrLn "Same:"
  print $ p'
  putStrLn "Invert polynomial:"
  print $ negate p
  putStrLn "Same:"
  print $ negate p'
  putStrLn "Check p == p:"
  print $ p == p
  putStrLn "Check p == !p:"
  print $ p == negate p
  putStrLn "Check p == p':"
  print $ p == p'
  putStrLn "Addition p + p':"
  print $ p + p'
  putStrLn "Addition of inverse p p + neg p, should be zero:"
  print $ p + (negate p)
  putStrLn "Substration p - p':"
  print $ p - p'
  putStrLn "Substraction p - p, should be zero:"
  print $ p - p
  putStrLn "Multiplication p * p':"
  print $ p * p'
  putStrLn "Absolute value of p:"
  print $ abs p
