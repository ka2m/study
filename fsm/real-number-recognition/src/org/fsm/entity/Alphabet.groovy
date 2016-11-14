package org.fsm.entity
/**
 * Created by vslepukhin on 18/09/2016.
 */
class Alphabet {
    String allAllowedChars
    List<Alpha> alphaList = []

    Alphabet(List alphabetConfig) {
        this.allAllowedChars = alphabetConfig.collect { it.validChars }.join ''
        alphabetConfig.each {
            this.alphaList << ([it.name, it.validChars] as Alpha)
        }
    }

    public Alpha converCharToAlpha(CharSequence c) throws Exception {
        if (!(this.allAllowedChars.contains(c))) {
            throw new Exception("This character is not allowed by this FSM")
        }
        return alphaList.find { it.validChars.contains(c) }
    }
}
