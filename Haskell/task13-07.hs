import Data.List

data Poly = IP (Int, Double)

-- only power equality!
instance Eq Poly where
  (==) p1 p2 = (power p1) == (power p2)
  (/=) p1 p2 = not (p1 == p2)

instance Ord Poly where
  (<) p1 p2 = (power p1) < (power p2)
  (>) p1 p2 = (power p1) > (power p2)

  compare p1 p2
    | p1 <= p2 = LT
    | p1 >= p2 = GT
    | p1 == p2 = EQ
    | otherwise = error "The intervals are non-comparable"

instance Show Poly where
    show (IP (x,y)) = "(" ++ show y ++"x^" ++ (show x ++ ")" ) ++ "+"

power :: Poly -> Int
power (IP (x, _)) = x

value :: Poly -> Double
value (IP (_, x)) = x

type Polynomial = [Poly]


findValueByPower :: Polynomial -> Int -> Double
findValueByPower p pw
  | p == [] = undefined
  | otherwise =
      if power (head  p) == pw
      then value  (head p)
      else findValueByPower (tail p) pw


printPolynomal :: Polynomial -> String
printPolynomal ps = reverse $ tail $ reverse $ (foldr (++) "" (map (show) ps))

powerList :: Polynomial -> [Int]
powerList l = foldr (:) [] (map (power) l)

sumPolynomials :: Polynomial -> Polynomial -> Polynomial
sumPolynomials p1 p2 = (p2 \\ p1) ++ (p1 \\ p2) ++ (reduceIntersections p1 p2)

reduceIntersections :: Polynomial -> Polynomial -> Polynomial
reduceIntersections p1 p2 =
  let
    first (p, _) = p
    second (_, p) = p
    s [] res = reverse res
    s (x : xs) res = s xs (IP((power (first x)), (value (first x)) + (value(second x))) : res)
  in
    s (zip (sort(intersectBy (\x y -> x == y) p1 p2))  (sort(intersectBy (\x y -> x == y) p2 p1)) ) []

invertPolynomial :: Polynomial -> Polynomial
invertPolynomial p = map (inv) p
  where inv pp = IP ((power pp), negate (value pp))

substractPolynomials :: Polynomial -> Polynomial -> Polynomial
substractPolynomials p1 p2 = sumPolynomials p1 (invertPolynomial p2)

test =
  let
    poly1 = IP (2, 5.0)
    poly2 = IP (0, 2.0)
    poly = [poly1, poly2]
    poly3 = IP (2, 6.0)
    poly4 = IP (1, 8.0)
    poly' = [poly3, poly4]
  in
    printPolynomal (substractPolynomials poly poly')
    -- invertPolynomial poly

main = do
  print $ test
