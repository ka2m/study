package org.fsm.fsmlib.machine

import org.fsm.fsmlib.entity.State
import org.fsm.fsmlib.entity.Alpha
import org.fsm.fsmlib.entity.Transition

/**
 * Created by vslepukhin on 18/09/2016.
 */
class FSMachine {
    State currentState
    FSMConfig fsm

    // dunno if needed
    Alpha lastConsumedCharcter

    public FSMachine(currentState, config) {
        this.currentState = currentState
        this.fsm = config
    }

    public List<Transition> feedChar(CharSequence aChar, boolean quiet) {
        try {
            def result = []
            Alpha a = this.fsm.alphabet.converCharToAlpha(aChar)
            this.lastConsumedCharcter = a
            this.fsm.transitionList.findAll { it.from == this.currentState && it.by == a }.each { Transition aT ->
                // add all transitions that are going to happen without any symbol (empty  symbol)
                this.fsm.transitionList.findAll { Transition t -> t.from == aT.to  && t.by.isEmptySymbol }.each {
                    result << it
                }
                result << aT
            }
            return result
        } catch(Exception ex) {
            if (!quiet)
                println ex.toString()
        }
    }
}
