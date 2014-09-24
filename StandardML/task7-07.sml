fun activation s =
  s/( (abs s) + 0.8)

type inputNeuron = { number: int
                   , connectedNeurons: int list
                   , output: real
                   }

fun makeInputNeuron ( neuronNumber, cnList, neuronOutput ) =
  { number = neuronNumber
  , connectedNeurons = cnList
  , output = neuronOutput
  }

type internalNeuron = { number: int
                      , connectedNeurons: int list
                      , offset: real
                      , output: real
                      }

fun makeInternalNeuron ( neuronNumber, cnList, neuronOffset, neuronOutput ) =
  { number = neuronNumber
  , connectedNeurons = cnList
  , offset = neuronOffset
  , output = neuronOutput
  }

type outputNeuron = { number: int
                    , output: int
                    }

fun makeOutputNeuron ( neuronNumber, neuronOutput ) =
  { number = neuronNumber
  , output = neuronOutput
  }

