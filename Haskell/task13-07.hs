import Data.List
import Numeric

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
  show (IT (x, y)) =
    let
      s (_, x) = x
      sh' = showFFloat (Just (if s (properFraction y) == 0 then 0 else 2)) y ""
    in
      if x == 0 && y /= 0 then sh'
      else if x == 1      then sh' ++ "x"
      else sh' ++ "x^" ++ show x

-- Helping functions

findTerm :: [Term] -> Term -> Term
findTerm [] y = IT (0, 0)
findTerm (x : xs) y
  | power x == power y = x
  | otherwise = findTerm xs y

normalize :: [Term] -> [Term]
normalize a =
  let
    reduce x xs = foldl (+) (IT (x, 0.0)) xs

    iter [] res       = res
    iter (x : xs) res =
      let
        (same, diff) = partition (\y -> power y == power x) (x : xs)
      in
        iter diff [reduce (power x) same] ++ res
  in
    sort (filter (\x -> value x /= 0) (iter a []))

-- Unwrap
terml :: Polynomial -> [Term]
terml (Polynomial p) = p

powp :: Polynomial -> Int
powp (Polynomial a) = power y where
  y = if null (normalize a)
      then IT (0, 0.0)
      else (normalize a) !! 0

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
      if (length p /= 0) && value (head p) > 0
      then tail v
      else if v == "" then "0.0" else v

instance Eq Polynomial where
  Polynomial a == Polynomial a' = vall a == vall a' where
    vall p = normalize p

instance Num Polynomial where
  Polynomial a + Polynomial a' =
    Polynomial (sort ((a \\ a') ++
                      (a' \\ a) ++
                      normalize ((intersectBy (\x y -> x == y) a a') ++
                                 (intersectBy (\x y -> x == y) a' a))))

  Polynomial a - Polynomial a' =
    Polynomial a + (negate (Polynomial a'))

  Polynomial a * Polynomial a' =
    Polynomial (normalize (multIter a a' []))
      where
        multIter [] [] res             = res
        multIter (x : xs) [] res       = multIter xs
                                                  (terml (Polynomial a'))
                                                  res
        multIter (x : xs) (y : ys) res = multIter (x : xs)
                                                  ys
                                                  [x * y] ++ res
        multIter _ _ res               = res

  abs (Polynomial a) = Polynomial [abs x | x <- a]
  negate (Polynomial a) = Polynomial [negate t | t <- a]

instance Real Polynomial where
  toRational a = 0.0

instance Ord Polynomial where
  a <= b = powp a <= powp b

instance Enum Polynomial where
  toEnum a = Polynomial [IT (0, 0.0)]
  fromEnum a = 1

instance Integral Polynomial where
  a `div` a' =
    let
      ta = Polynomial (normalize (terml a))
      ta' = Polynomial (normalize (terml a'))

      iter a a' res
        | powp a < powp a'
          || null (normalize (terml a))
          || null (normalize (terml a')) = Polynomial (res)
        | otherwise =
          let
            t = head (normalize (terml a))
            t' = head (normalize (terml a'))
            tp = power t
            tp' = power t'
            t'' = IT (tp - tp', (value t) / (value t'))
            tmp'' = Polynomial [t''] * a'
            sub = a - tmp''
          in
            iter sub a' ([t''] ++ res)
    in
      iter ta ta' []

  a `mod` a' = a - (a `div` a') * a'
  a `divMod` a' = (a `div` a', a `mod` a')
  a `quotRem` a' = (a, a')
  toInteger a = 0

-- Examples
a1 = IT (0, 1.0)
a2 = IT (1, -2.0)
a3 = IT (2, 3.0)
p = Polynomial [a1, a2, a3]
p'' = Polynomial [a2, a1, a3]

a0' = IT (4, 7.0)
a1' = IT (3, 4.0)
a2' = IT (2, 8.0)
p' = Polynomial [a0', a1', a2']

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
  putStrLn "Check p == p'':"
  print $ p == p''
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
  putStrLn "p' div p:"
  print $ p' `div` p
  putStrLn "p' / p (should give 0.0):"
  print $ p `div` p'
  print $ divMod p p''
  print $ divMod p p'
  print $ divMod p' p
