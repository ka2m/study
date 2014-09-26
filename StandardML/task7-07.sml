load "ListPair";
load "List";

fun activation (s, apply) =
  if apply 
  then s / ( (abs s) + 0.8)
  else s 

fun reverseBack ([], l)      = l
|   reverseBack (x :: xs, l) = reverseBack (xs, x :: l)

fun first (number:int, weight:int) = number
fun second (number:int, weight:int) = weight

structure NeuralNetwork = struct

  type neuron = { weights: int list
                , shift: real
                , output: real
                , isEdge: bool
                }

  fun makeHiddenNeuron ( nacs, nsh ) =
    { weights = nacs
    , shift = nsh
    , output = 0.0
    , isOutput = false
    }

  fun makeOutputLayer ( nacs, nsh ) =
    { weights = nacs
    , shift = nsh
    , output = 0.0
    , isOutput = true
    }

  fun neuronWeights ({ weights = w, ...} : neuron) = w
  fun neuronShift ({shift = s, ...} : neuron) = s
  fun neuronIsOutput ({isOutput = e, ...} : neuron) = e

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

  type layers = (neuron list) list  

  type neuralNetwork = { ilayer: neuron list
                       , hlayers: layers
                       }

  fun initNeuralNetwork ( inl, hls ) =
    { ilayer = inl
    , hlayers = hls 
    }

  fun networkInputLayer ({ilayer = i, ...} : neuralNetwork) = i
  fun networkInternals ({hlayers = h, ...} : neuralNetwork) = h

  fun evaluateNetwork ( input, hidden ) =
    let
      fun evaluateNeuronSum [] [] res = res
      |   evaluateNeuronSum (x::xs) (y::ys) res =
            evaluateNeuronSum xs ys res + (x*y)

      fun evaluateLayer [] previousResults res = res
      |   evaluateLayer x::xs previousResults res = 
            evaluateLayer xs 
                          previousResults
                          ((activation (evaluateNeuronSum, (neuronIsOutput x))
                            + (neuronShift x)) :: res)
                          
      fun evaluateNetwork previous [] res = res
      |   evaluateNetwork previous (x::xs) res =
            evaluateNetwork x xs (evaluateLayer x previous [])


      
      in
        evaluateNetwork input hidden []
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
    val olayer = NeuralNetwork.makeOutputLayer ( [ ([1, 2, 3], 1.1), 
                                                   ([2, 1, 3], 2.3) ] )
  in
    NeuralNetwork.initNeuralNetwork (inputLayer, [hlayer, olayer] )
  end

NeuralNetwork.evaluateNetwork ( (networkInputLayer nn), (networkInternals nn))





