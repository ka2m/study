signature NN = 
sig
  type neuron 
  type neuralNetwork
  val makeLayer : (real list * real) list * bool -> neuron list
  val initNeuralNetwork : real * (neuron list) list -> neuralNetwork
  val eval : neuralNetwork -> real list
end

structure NeuralNetwork = struct
  
  fun activation (s, isOutput) =
    if isOutput
    then s
    else s / ( (abs s) + 0.8)

  type neuron = { weights: real list
                , shift: real
                , isOutput: bool
                }

  fun makeHiddenNeuron ( nacs, nsh ) =
    { weights = nacs
    , shift = nsh    
    , isOutput = false
    }

  fun makeOutputNeuron ( nacs, nsh ) =
    { weights = nacs
    , shift = nsh
    , isOutput = true
    }

  fun neuronWeights ({ weights = w, ...} : neuron) = w
  fun neuronShift ({shift = s, ...} : neuron) = s
  fun neuronIsOutput ({isOutput = e, ...} : neuron) = e

  fun makeLayer ( values, isOutput ) =
    let
      fun first' (a: real list, b: real) = a
      fun second' (a: real list, b: real) = b

      fun add [] res      = rev res
      |   add (x::xs) res =
            add xs (if isOutput
                    then makeOutputNeuron ( (first' x), (second' x) ) :: res
                    else makeHiddenNeuron ( (first' x), (second' x) ) :: res
                      )
    in
      add values []
    end

  type neuralNetwork = { ilayer: real list
                       , hlayers: (neuron list) list
                       }

  fun initNeuralNetwork ( inl, hls ) =
    { ilayer = inl
    , hlayers = hls
    }

  fun networkInputLayer ({ilayer = i, ...} : neuralNetwork) = i
  fun networkInternals ({hlayers = h, ...} : neuralNetwork) = h

  fun eval ( network ) = 
    let
      fun evalUnwrapped ( input, hidden ) =
        let
          fun evaluateNeuronSum [] [] res           = res
          |   evaluateNeuronSum (x::xs) (y::ys) res =
                evaluateNeuronSum xs ys res + (x * y)

          fun evaluateNeuron previous n =
            activation ( ((evaluateNeuronSum previous (neuronWeights n) 0.0) +
                         (neuronShift n)), (neuronIsOutput n) )

          (*  evalLayer previousResults currentNeuronLayer resultingList *)
          fun evaluateLayer previous [] res      = res
          |   evaluateLayer previous (x::xs) res =
                evaluateLayer previous xs ((evaluateNeuron previous x) :: res)

          fun evaluateNetwork previous []      = previous
          |   evaluateNetwork previous (x::xs) =
                evaluateNetwork (evaluateLayer previous x []) xs 
        in
            evaluateNetwork input hidden
        end
    in
      evalUnwrapped ( (networkInputLayer network), (networkInternals network) )
    end
end

(*****************************************************************************
                                Example
 ****************************************************************************)
val nn =
let
  val inputLayer = [1.0, 2.0, 3.0]
  val hlayer = NeuralNetwork.makeLayer ([ ([3.0, 2.0, 1.0], 0.5), 
                                            ([1.0, 2.0, 3.0], 0.75) ], false)
  val olayer = NeuralNetwork.makeLayer ([ ([1.0, 2.0], 0.125) ], true)
in
  NeuralNetwork.initNeuralNetwork ( inputLayer, [hlayer, olayer] )
end

val p = NeuralNetwork.eval (nn)
