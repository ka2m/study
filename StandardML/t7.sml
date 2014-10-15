signature NN = 
sig
  type neuron 
  type neuralNetwork
  val makeLayer : (real list * real) list * bool -> neuron list
  val initNeuralNetwork : int * (neuron list) list -> neuralNetwork
  val eval : neuralNetwork * real list * (real -> real) -> real list
end

structure NeuralNetwork = struct

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

  type neuralNetwork = { inputNeurons: int
                       , hlayers: (neuron list) list
                       }

  fun initNeuralNetwork ( ins, hls ) =
    { inputNeurons = ins
    , hlayers = hls
    }
 
  fun inNeurons ({inputNeurons = n, ...} : neuralNetwork) = n
  fun networkInternals ({hlayers = h, ...} : neuralNetwork) = h
  fun networkHiddenLayers network = rev (tl (rev (networkInternals network)))
  fun networkOutputLayer network = hd (rev (networkInternals network))

  fun evaluateNeuronSum [x] [] _            = 0.0 
  |   evaluateNeuronSum [] [x] _            = 0.0
  |   evaluateNeuronSum [] [] res           = res
  |   evaluateNeuronSum (x::xs) (y::ys) res =
        evaluateNeuronSum xs ys res + (x * y)

  (*  evalLayer activFn previousResults currentNeuronLayer resultingList *)
  fun evaluateLayer afn previous [] res      = res
  |   evaluateLayer afn previous (x::xs) res =
        let
          fun evaluateNeuron previous n =
            let 
              val s = ( (evaluateNeuronSum previous (neuronWeights n) 0.0) +
                        (neuronShift n) )
            in
              if (neuronIsOutput n)
              then s
              else afn s
            end
        in
          evaluateLayer afn previous xs ((evaluateNeuron previous x) :: res)
        end
        
  fun eval ( network, input, activationFn ) = 
    let
      fun evalUnwrapped ( input, hidden ) =
        let
          fun evaluateNetwork previous []        = previous
          |   evaluateNetwork previous (x :: xs) =
                evaluateNetwork (evaluateLayer activationFn previous x []) xs
        in
          evaluateNetwork input hidden
        end
    in
      evalUnwrapped ( input, (networkInternals network) )
    end


       
    
  fun train ( network, trainingExamplesInputs, desiredOutputs
            , activationFn, derivative, rate, generations ) =
    let
      (* print runtime neuron output values, packed in lists by layers *)
      fun verboseNetworkOutput inputExample nn =
        let
          fun evaluateLayerResults previous []  res       = res
          |   evaluateLayerResults previous (x :: xs) res = 
                let 
                  val p = evaluateLayer activationFn previous x []
                in
                  evaluateLayerResults p xs (p :: res)
                end      
        in
          evaluateLayerResults inputExample (networkInternals nn) []
        end

      fun verboseNetworkOutputForAll [] res nn        = res
      |   verboseNetworkOutputForAll (x :: xs) res nn =
            verboseNetworkOutputForAll xs 
                                       (( verboseNetworkOutput x nn ) :: res)
                                       nn

      fun evalOutputDeltaSum expectedOutputNeuronValue trainingOutputs  =
        foldr (op +) 
              0.0
              (map  
                (fn x => (expectedOutputNeuronValue - x ) * (derivative x) * x)
                trainingOutputs)
          

      fun updateNeuronWeight oldWeight expected training =
        oldWeight + rate * (evalOutputDeltaSum expected training)


      fun updateOutputNeuron oldNeuron rv dv = 
          let            
            fun upd [] shift res        = makeOutputNeuron (rev res, shift)
            |   upd (x :: xs) shift res = 
                  upd xs shift ((updateNeuronWeight x dv rv) :: res)
          in
            upd (neuronWeights oldNeuron) (neuronShift oldNeuron) []
          end

      (* updateOutputLayer neuronList realValueList desiredValList resultNL *)
      (* apply updates to each neuron *)
      fun updateOutputLayer [] [] [] res                      = rev res
      |   updateOutputLayer (n :: ns) (r :: rs) (d :: ds) res =
            updateOutputLayer ns rs ds ((updateOutputNeuron n r d) :: res)


      (* covnert outputs for iterating over TRAINING result list instead
         of output layer list *)
      fun convert' [[], _] res = rev res
      |   convert' output res =
            convert' (foldr (op ::) [] (map (tl) output))
                     ((map (hd) output) :: res)
    
      fun eq ([], [])               = true
      |   eq ((x :: xs), (y :: ys)) =
            if x > ( y - 0.0001 ) andalso x < ( y + 0.0001 )  
            then eq (xs, ys)
            else false


      fun iterate nn iter =
        let
          val hls = (networkHiddenLayers nn)
          val exampleVerboseOutput = 
            verboseNetworkOutputForAll trainingExamplesInputs [] nn
          val exampleOutputLayerValues = map (hd) exampleVerboseOutput
          val oldOutputNeuronList = (networkOutputLayer nn)
          val realOutputValueListByExample = 
            (convert' exampleOutputLayerValues [])
          val newOutputLayer = 
            updateOutputLayer oldOutputNeuronList 
                              realOutputValueListByExample
                              desiredOutputs
                              []
          val newNeuralNetwork = initNeuralNetwork ( (inNeurons nn)
                                                   ,  hls @ [newOutputLayer] )
          (*val updatedOutput = (hd (verboseNetworkOutput nnn))*)

        in
           (*if (eq (desiredOutputs,  updatedOutput)) orelse iter = 0*)
           (*if iter = 0
           then newNeuralNetwork
           else iterate newNeuralNetwork (iter - 1)*)
           newNeuralNetwork
        end

    in
      iterate network generations
    end
  end


(*****************************************************************************
                                Example
 ****************************************************************************)
val nn =
let
  val hlayer = NeuralNetwork.makeLayer ([ ([0.1, 0.2, 0.3], 0.05), 
                                          ([0.3, 0.2, 0.1], 0.075),
                                          ([0.5, 0.2, 0.4], 0.095) ], false)
  val olayer = NeuralNetwork.makeLayer ([ ([0.6, 0.8], 0.0125),
                                          ([0.9, 0.2], 0.0855) ], true)
in
  NeuralNetwork.initNeuralNetwork ( 3, [hlayer, olayer] )
end


fun p s = (abs s) + 0.8
fun activation s =  s / (p s)
fun derivative s =  (~(s * s)/abs (s) + (p s))/((p s) * (p s))

val inputValues = [[1.0, 2.0, 3.0]]
val inputValues = rev ( [5.0, 6.0, 7.0] :: inputValues )

val e = 
  let
    fun activation s =  s / ( (abs s) + 0.8)
  in
    NeuralNetwork.eval (nn, (hd inputValues), activation)
  end


val desiredOutput = [2.0, 1.0]
val rate = 0.0001
val p = NeuralNetwork.train ( nn
                            , inputValues
                            , desiredOutput
                            , activation
                            , derivative
                            , rate
                            , 100
                            )