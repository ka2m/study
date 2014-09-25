fun activation s =
  s / ( (abs s) + 0.8)

fun reverseBack ([], l)      = l
|   reverseBack (x :: xs, l) = reverseBack (xs, x :: l)

fun first (number:int, weight:int) = number
fun second (number:int, weight:int) = weight


structure NeuralNetwork = struct
  type inputNeuron = real

  type hiddenNeuron = { weights: int list
                      , shift: real
                      , output: real
                      }

  fun makeHiddenNeuron ( nacs, nsh ) =
    { weights = nacs
    , shift = nsh
    , output = 0.0
    }

  fun makeHiddenLayer ( values ) =
    let
      fun first' (a: int list, b: real) = a
      fun second' (a: int list, b: real) = b

      fun add [] res = reverseBack (res, [])
      |   add (x::xs) res =
            add xs (makeHiddenNeuron ( (first' x), (second' x) ) :: res)
    in
      add values []
    end

  type inList = inputNeuron list
  type layers = (hiddenNeuron list) list
  type outList = hiddenNeuron list

  type neuralNetwork = { ilayer: inList
                       , hlayers: layers
                       , olayer: outList
                       }

  fun initNeuralNetwork ( inl, hls, ol ) =
    { ilayer = inl
    , hlayers = hls 
    , olayer = ol
    }
end

(*****************************************************************************
                                Example
 ****************************************************************************)


val nn = 
  let
    val inputLayer = [1.0, 2.0, 3.0, 4.0, 5.0]
    val hlayer = NeuralNetwork.makeHiddenLayer (
              [ ( [1, 2, 3, 4, 5], 1.25)
              , ( [3, 2, 1, 5, 4], 2.35)
              , ( [5, 4, 2, 3, 1], 3.15)])
    val olayer = NeuralNetwork.makeHiddenLayer ( [ ([1, 2, 3], 1.1), 
                                                   ([2, 1, 3], 2.3) ] )
  in
    NeuralNetwork.initNeuralNetwork (inputLayer, [hlayer], olayer)
  end







