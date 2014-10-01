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

  fun train ( network, inputs, outputs, retries, rate, afn, derivative ) =
    let
      (* print runtime neuron output values, packed in lists by layers *)
      fun verboseNetworkOutput nn =
        let
          fun evaluateLayerResults previous []  res       = res
          |   evaluateLayerResults previous (x :: xs) res = 
                let 
                  val p = evaluateLayer afn previous x []
                in
                  evaluateLayerResults p xs (p :: res)
                end      
        in
          evaluateLayerResults inputs (networkInternals nn) []     
        end

      fun updateNeuronWeight oldWeight realValue desireValue =
        oldWeight + ( ~ 1.0 * rate * 
        ( realValue - desireValue ) * (derivative realValue) * realValue )

      (*  updateOutputNeuron oldWeights neuronShift realValue desiredValue *)
      (*  set new synapse weight *)
      fun updateOutputNeuron oldNeuron rv dv = 
          let            
            fun upd [] shift res        = makeOutputNeuron (res, shift)
            |   upd (x :: xs) shift res = 
                  upd xs shift ((updateNeuronWeight x rv dv) :: res)
          in
            upd (neuronWeights oldNeuron) (neuronShift oldNeuron) []
          end

      (* updateOutputLayer neuronList realValueList desiredValList resultNL *)
      (* apply updates to each neuron *)
      fun updateOutputLayer [] [] [] res                      = res
      |   updateOutputLayer (n :: ns) (r :: rs) (d :: ds) res =
            updateOutputLayer ns rs ds ((updateOutputNeuron n r d) :: res)

      (* check if outputs are equal with some precision *)
      fun eq ([], [])               = true
      |   eq ((x :: xs), (y :: ys)) =
            if x > ( y - 0.0001 ) andalso x < ( y + 0.0001 )  
            then eq (xs, ys)
            else false
      
      fun iterate nn iter = 
        let          
          val hls = networkHiddenLayers nn
          val ol = updateOutputLayer (networkOutputLayer nn)
                                     (hd (verboseNetworkOutput nn)) 
                                     outputs
                                     []
          val nnn = initNeuralNetwork ( (inNeurons nn), hls @ [ol])
          val updatedOutput = (hd (verboseNetworkOutput nnn))
         in
           if (eq (outputs,  updatedOutput)) orelse iter = 0
           then nnn
           else iterate nnn (iter - 1)
         end 
    in
      iterate network retries
    end
end

(*****************************************************************************
                                Example
 ****************************************************************************)
val nn =
let
  val hlayer = NeuralNetwork.makeLayer ([ ([0.1, 0.2, 0.3], 0.05), 
                                          ([0.3, 0.2, 0.1], 0.075) ], false)
  val olayer = NeuralNetwork.makeLayer ([ ([0.6, 0.8], 0.0125) ], true)
in
  NeuralNetwork.initNeuralNetwork ( 3, [hlayer, olayer] )
end


fun p s = (abs s) + 0.8
fun activation s =  s / (p s)
fun derivative s =  (~(s * s)/abs (s) + (p s))/((p s) * (p s))

val inputValues = [1.0, 2.0, 3.0]

val e = 
  let
    fun activation s =  s / ( (abs s) + 0.8)
  in
    NeuralNetwork.eval (nn, inputValues, activation)
  end


val trainer = 
  NeuralNetwork.eval ( NeuralNetwork.train ( nn
                                           , inputValues
                                           , [2.0]
                                           , 100000
                                           , 0.00025  
                                           , activation
                                           , derivative )
                     , inputValues
                     , activation)



