package org.fsm.fsmlib.machine

import org.fsm.fsmlib.entity.Alpha
import org.fsm.fsmlib.entity.Alphabet
import org.fsm.fsmlib.entity.State
import org.fsm.fsmlib.entity.Transition
import org.fsm.fsmlib.generator.ReadRegex

/**
 * Created by vslepukhin on 18/09/2016.
 */
class FSMConfig {
    Alphabet alphabet
    List<State> stateList = []
    List<Transition> transitionList

    FSMConfig(Alphabet alphabet, List<State> stateList, List<Transition> transitionList) {
        this.alphabet = alphabet
        this.stateList = stateList
        this.transitionList = transitionList
    }

    public FSMConfig(Map config) {
        this.alphabet = new Alphabet(config.alphabet)
        this.transitionList = []
        config.states.each { stateList << ([it.name, it.starting, it.final] as State)}
        config.transitions.each { t ->
            State fromState = stateList.find { it.name == t.from }
            State toState = stateList.find { it.name == t.to }
            Alpha a = alphabet.alphaList.find { it.name == t.by}
            this.transitionList << ([fromState, toState, a] as Transition)
        }
    }

    public FSMConfig(String regex) {
        def fsmFromRegex = ReadRegex.readRegexString(regex)
        this.alphabet = fsmFromRegex.alphabet
        this.stateList = fsmFromRegex.stateList
        this.transitionList = fsmFromRegex.transitionList
    }


    public describe() {
        println "This FSM has the following alphabet:"
        this.alphabet.alphaList.each {println it}

        println "\nTotal allowed charcter list: ${this.alphabet.allAllowedChars}"

        println "\nThis FSM has the following states with names:"
        this.stateList.each { print "${it.name} " }

        println "\n\nInitial (starting) states are:"
        this.stateList.findAll { it.isStarting}.each { s -> print "${s.name} " }

        println "\n\nFinal states are:"
        this.stateList.findAll { it.isFinal}.each { s -> print "${s.name} " }

        println "\n\n"

        this.transitionList.each {
            println "${it.from} -> ${it.to} by ${it.by}"
        }

    }

    @Override
    public String toString() {
        return "FSMConfig{" +
                "alphabet=" + alphabet +
                ", stateList=" + stateList +
                ", transitionList=" + transitionList +
                '}';
    }
}
