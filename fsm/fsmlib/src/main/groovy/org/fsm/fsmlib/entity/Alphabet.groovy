package org.fsm.fsmlib.entity
/**
 * Created by vslepukhin on 18/09/2016.
 */
class Alphabet {
    String allAllowedChars
    List<Alpha> alphaList = []

    Alphabet() {
        this.allAllowedChars = ""
    }

    Alphabet(List alphabetConfig) {
        this.allAllowedChars = alphabetConfig.collect { Map m -> (m.containsKey("validChars"))? m.validChars : '' }.join ''
        alphabetConfig.each { Map m ->
            if (m.containsKey("validChars")) {
                this.alphaList << ([m.name, m.validChars] as Alpha)
            } else {
                this.alphaList << ([m.name] as Alpha)
            }
        }
    }

    def addAlpha(Alpha a) {
        this.alphaList << a
        this.allAllowedChars = ((this.allAllowedChars + a.validChars) as List).unique().join('')
    }

    public Alpha converCharToAlpha(CharSequence c) throws Exception {
        if (!(this.allAllowedChars.contains(c))) {
            throw new Exception("This character is not allowed by this FSM")
        }
        return alphaList.find { it.validChars.contains(c) }
    }

    @Override
    public String toString() {
        return "Alphabet{" +
                "allAllowedChars='" + allAllowedChars + '\'' +
                ", alphaList=" + alphaList +
                '}';
    }
}
