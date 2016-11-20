package org.fsm.fsmlib.machine

import org.fsm.fsmlib.entity.Alpha
import org.fsm.fsmlib.entity.Alphabet
import org.fsm.fsmlib.entity.State
import org.fsm.fsmlib.entity.Transition
import org.fsm.fsmlib.generator.helper.RegexSymbol

import java.security.MessageDigest

/**
 * Created by vslepukhin on 17/11/2016.
 */
abstract class FSMTransform {

    /**
     * Performs unity operation (\+)
     * Example:
     * FSM1: nulls -> a -> finals
     * FSM2: nulls -> b -> finals
     *
     *                -> a -
     * RES: nulls - <        > finals
     *                -> b -
     */
    static def unite(FSMConfig a, FSMConfig b) {
        def newAlphabet = getNewAlphabet(a.alphabet, b.alphabet)
        def newStates = getNewStates(a.stateList, b.stateList)
        def newTransitions = []

        a.transitionList.each { newTransitions << it}
        b.transitionList.each { newTransitions << it}

        return new FSMConfig(newAlphabet, newStates, newTransitions)
    }

    /**
     * Performs iteration operation (\*)
     * Example:
     * FSM: nulls -> a -> finals
     *
     *                  /-\
     *                  \ V
     *                -> a -
     * RES: nulls - <        > finals
     *                -------
     */
    static def iterate(FSMConfig a) {
        def newAlphabet = new Alphabet()
        a.alphabet.alphaList.each { Alpha al ->
            newAlphabet.addAlpha(al)
        }

        def newStates = [a.stateList.find {State s -> s.isStarting }]
        a.stateList.findAll { State s -> !s.isStarting }.each {
            newStates << it
        }

        def newTransitions = []
        a.transitionList.each { newTransitions << it}

        for(Transition t: a.transitionList) {
            if (t.to.isFinal && t.by.isEmptySymbol) {
                State s = t.from
                List<Transition> foundSame = a.transitionList.findAll { it.from.isStarting }
                foundSame.each {
                    newTransitions << new Transition(s, it.to, it.by)
                }
            }
        }

        newStates.findAll { State t -> t.isStarting }.each { ss ->
            def allFinal = newStates.findAll { State t -> t.isFinal }
            def emptySymbol = newAlphabet.alphaList.find { it.isEmptySymbol }
            allFinal.each { fs ->
                newTransitions << new Transition(ss, fs, emptySymbol)
            }
        }

        return new FSMConfig(newAlphabet, newStates, newTransitions.unique())
    }

    static def concat(FSMConfig a, FSMConfig b) {
        def newAlphabet = getNewAlphabet(a.alphabet, b.alphabet)
        def newStates = getNewStates(a.stateList, b.stateList)
        def newTransitions = []

        def aTransitionsToBeConnected = a.transitionList.findAll { it.to.isFinal }
        def bTransitionsToBeConnected = b.transitionList.findAll{ it.from.isStarting }

        a.transitionList.findAll { !aTransitionsToBeConnected.contains(it)}.each { newTransitions << it}

        aTransitionsToBeConnected.each { fromT ->
            bTransitionsToBeConnected.each { toT ->
                newTransitions << new Transition(fromT.from, toT.to, toT.by)
            }
        }


        b.transitionList.findAll{ !bTransitionsToBeConnected.contains(it)}.each {newTransitions << it}


        return new FSMConfig(newAlphabet, newStates, newTransitions.unique())
    }


    static def generateBasicFSM(RegexSymbol rs, String buf = null) {
        def emptyAlpha = ["name": "emptyA"]
        def addingAlpha

        if (rs == RegexSymbol.AnyNumber) {
            addingAlpha = ["name": "number", "validChars": "0123456789"]
        }
        else if (rs == RegexSymbol.AnySymbol) {
            addingAlpha = ["name": "engChar", "validChars": "qazwsxedcrfvtgbyhnujmikolpQAZWSXEDCRFVTGBYHNUJMIKOLP"]
        } else {
            addingAlpha = ["name": "exactChar-${buf}", "validChars": buf]
        }
        def aName = getRandomName()

        def states = [["name": "nulls", "starting": true],
                      ["name": aName],
                      ["name": "finals", "final": true]]

        def transitions = [["from": "nulls", "to": aName, "by": addingAlpha.name],
                           ["from": aName, "to": "finals", "by": emptyAlpha.name]]

        def fsmConfig = ["alphabet": [emptyAlpha, addingAlpha],
                         "states": states,
                         "transitions": transitions]


        return new FSMConfig(fsmConfig)
    }

    static def reduceIterate(List actionItems) {
        for (int i = 0; i < actionItems.size() - 1; i++) {
            if (actionItems[i] instanceof FSMConfig && actionItems[i + 1] == RegexSymbol.Iterate) {
                FSMConfig newFSM = iterate(actionItems[i] as FSMConfig)
                actionItems[i] = null
                actionItems[i + 1] = newFSM
            }

        }
        actionItems.removeIf { it == null }
        return actionItems
    }

    static def reduceUnite(List actionItems) {
        for (int i = 0; i < actionItems.size() - 2; i++) {
            if (actionItems[i] instanceof FSMConfig && actionItems[i + 1] == RegexSymbol.Unite && actionItems[i + 2] instanceof FSMConfig) {
                FSMConfig newFSM = unite(actionItems[i] as FSMConfig, actionItems[i + 2] as FSMConfig)
                actionItems[i] = null
                actionItems[i + 1] = null
                actionItems[i + 2] = newFSM
            }
        }
        actionItems.removeIf { it == null }

        return actionItems
    }

    static def reduceConcat(List actionItems) {
        for (int i = 0; i < actionItems.size() - 1; i++) {
            if (actionItems[i] instanceof FSMConfig && actionItems[i + 1] instanceof FSMConfig) {
                FSMConfig newFSM = concat(actionItems[i] as FSMConfig, actionItems[i + 1] as FSMConfig)
                actionItems[i] = null
                actionItems[i + 1] = newFSM
            }
        }
        actionItems.removeIf { it == null }
        return actionItems
    }

    static def reduceList(List actionItems, boolean cutParanthesis) {
        if (cutParanthesis) {
            actionItems[0] = null
            actionItems[-1] = null
        }

        while(actionItems.find { it == RegexSymbol.Iterate } != null) actionItems = reduceIterate(actionItems)
        while(hasUnDoneConcat(actionItems)) actionItems = reduceConcat(actionItems)


        return reduceUnite(actionItems)
    }

    static def hasUnDoneConcat(List actionItems) {
        for (int i = 0; i < actionItems.size() - 1; i++) {
            if (actionItems[i] instanceof FSMConfig && actionItems[i + 1] instanceof FSMConfig) {
                return true
            }
        }
        return false
    }

    static def getRandomName() {
        MessageDigest sha1 = MessageDigest.getInstance("SHA1")
        byte[] digest  = sha1.digest((System.currentTimeMillis() as String).getBytes())
        return new  BigInteger(1, digest).toString().take(6)
    }

    static def getNewAlphabet(Alphabet a, Alphabet b) {
        def newAlphabet = new Alphabet()
        def newAlphaList = a.alphaList
        newAlphaList.addAll(b.alphaList)

        newAlphaList.unique().each { Alpha al ->
            newAlphabet.addAlpha(al)
        }
        return newAlphabet
    }

    static def getNewStates(List<State> a, List<State> b) {
        def newStates = [a.find {State s -> s.isStarting }]
        a.findAll { State s -> !s.isStarting }.each {
            newStates << it
        }
        b.findAll { State s -> !s.isStarting }.each {
            newStates << it
        }
        return newStates.unique()
    }

}
