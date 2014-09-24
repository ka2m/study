fun activation s =
  s / ( (abs s) + 0.8)

structure NeuralNetwork = struct
  structure InputNeuron = struct  
    type number = int  
    type output = real
  end

  structure HiddenNeuron = struct
    type number = int
    type ancestors = int * int list
    type shift = real
    type output = real
  end

  structure OutputNeuron = struct
    type number = int
    type output = real
  end

  type inList = InputNeuron list
  type internalList = HiddenNeuron list
  type outList = OutputNeuron list
end

(*****************************************************************************
                                Example
 ****************************************************************************)
