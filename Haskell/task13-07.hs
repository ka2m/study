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

data PP = List(Poly)

findValueByPower :: Polynomial -> Int -> Double
findValueByPower p pw
  | p == [] = 0
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

convertToNormalForm :: Polynomial -> [Double]
convertToNormalForm p =
  let
    pl = reverse $ [x | x <- [0 .. head $ reverse $ sort (powerList p)]]
    iter  [] res = reverse res
    iter (x : xs) res = iter xs ((findValueByPower p x) : res)
  in
    iter pl []

reverseConvert :: [Double] -> Polynomial
reverseConvert bareList =
  let
    rc' c [] res = reverse res
    rc' c (x:xs) res = rc' (c-1)
                           xs
                           (if (x /= 0.0) then (IP (c, x) : res) else res)
  in
    rc' (length (bareList) - 1) bareList []

multiplyPolynomials :: Polynomial -> Polynomial -> Polynomial
multiplyPolynomials p1 p2 =
  let
    timesPoly c p1 = map (c*) p1
    -- Multiply two polynomials
    multPoly [] p2 = []
    multPoly (p:p1) p2 =
      let
        multiplyByX p = 0:p

        pTimesP2 = timesPoly p p2
        xTimesP1TimesP2 = multiplyByX $ multPoly p1 p2

        addPoly [] []     = []
        addPoly (x:xs) [] = x : addPoly xs []
        addPoly [] (y:ys) = y : addPoly [] ys
        addPoly (x:xs) (y:ys) = x + y : addPoly xs ys
      in
        addPoly pTimesP2 xTimesP1TimesP2
  in
    reverseConvert ( multPoly (convertToNormalForm p1) (convertToNormalForm p2) )


test =
  let
    poly1 = IP (2, 5.0)
    poly2 = IP (0, 2.0)
    poly = [poly1, poly2]
    poly3 = IP (2, 6.0)
    poly4 = IP (1, 8.0)
    poly' = [poly3, poly4]
  in
    -- printPolynomal (substractPolynomials poly poly')
    printPolynomal $ multiplyPolynomials poly poly'

main = do
  print $ test
