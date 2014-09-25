fun activation s =
  s / ( (abs s) + 0.8)

fun reverseBack ([], l)      = l
|   reverseBack (x :: xs, l) = reverseBack (xs, x :: l)

fun first (number:int, weight:int) = number
fun second (number:int, weight:int) = weight


structure NeuralNetwork = struct
  type inputNeuron = { number: int
                     , output: real
                     }
  
  fun makeInputNeuron ( nnum, value ) =
    { number = nnum
    , output = value
    }

  fun makeInputLayer ( values ) =
    let
      fun add [] i res = reverseBack (res, [])
      |   add (x::xs) i res =
            add xs (i+1) (makeInputNeuron ( i, x ) :: res)
    in
      add values 1 []
    end

  type hiddenNeuron = { number: int
                      , ancestors: int * int list
                      , shift: real
                      , output: real
                      }

  fun makeHiddenNeuron ( nnum, nacs, nsh ) =
    { number = nnum
    , ancestors = nacs
    , shift = nsh
    , output = 0.0
    }

  fun makeHiddenLayer ( values ) =
    let
      fun first' (ancestors: (int * int) list, shift: real) = ancestors
      fun second' (ancestors: (int * int) list, shift: real) = shift

      fun add [] i res = reverseBack (res, [])
      |   add (x::xs) i res =
            add xs (i+1) (makeHiddenNeuron ( i, 
                                             (first' x), (second' x) ) :: res)
    in
      add values 1 []
    end

  type outputNeuron = { number: int
                      , ancestors: int * int list
                      , output: real
                      }

  fun makeOutputNeuron ( nnum, nacs ) =
    { number = nnum
    , ancestors = nacs
    , output = 0.0
    }

  fun makeOutputLayer ( values ) = 
    let
      fun add [] i res = reverseBack (res, [])
      |   add (x::xs) i res =
            add xs (i+1) ( makeOutputNeuron ( i, x ) :: res )
    in
      add values 1 []
    end

  fun makeNeuralNetwork ( inputList, intlList, outputList ) =
    { inList = inputList
    , internalList = intlList
    , outList = outputList
    }

  type inList = inputNeuron list
  type internalList = (hiddenNeuron list) list
  type outList = outputNeuron list
end

(*****************************************************************************
                                Example
 ****************************************************************************)

val ilayer = NeuralNetwork.makeInputLayer ( [ 1.0 
                                          , 2.0
                                          , 3.0
                                          , 4.0
                                          , 5.0] )

val hlayer = NeuralNetwork.makeHiddenLayer (
              [ ( [(1, 1), (2, 1), (3, 2), (4, 5), (5, 6)]
                , 1.25)
              , ( [(1, 3), (2, 2), (3, 1), (4, 2), (5, 3)]
                , 2.25)
              , ( [(1, 5), (2, 3), (3, 2), (4, 1), (5, 1)]
                , 3.15) 
              ] )

val olayer = NeuralNetwork.makeOutputLayer ( [ (1, 1), (2, 2), (3, 3)
                                             , (1, 2), (2, 1), (3, 2)
                                             ] )

val nn = NeuralNetwork.makeNeuralNetwork ( ilayer, [hlayer], olayer );










