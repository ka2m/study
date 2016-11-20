package org.fsm.fsmlib.runner

import groovy.json.JsonSlurper
import org.fsm.fsmlib.machine.FSMConfig
import org.fsm.fsmlib.machine.FSMachine

/**
 * Created by vslepukhin on 18/09/2016.
 */
class FSMRunner {
    FSMConfig fsmConfig

    boolean quiet = false

    public FSMRunner(File configFile, boolean quiet = false) {
        def data = new JsonSlurper().parse(configFile)
        this.fsmConfig = new FSMConfig(data)
        this.quiet = quiet
        if (!quiet)
            this.fsmConfig.describe()
    }

    public FSMRunner(String regexString, boolean quiet = false) {
        this.fsmConfig = new FSMConfig(regexString)
        if (!quiet)
            this.fsmConfig.describe()
    }

    public FSMRunner(FSMConfig config, boolean quiet =false) {
        this.fsmConfig = fsmConfig
        this.quiet = quiet
    }

    public void run(String inputString) {
        println 'Must be implemented in FSM instance'
    }

    public List tickMachine(List<FSMachine> currentMachineList, CharSequence aChar) {
        def newStates = []
        currentMachineList.each { FSMachine m -> newStates << m.feedChar(aChar, this.quiet) }
        return newStates.flatten().unique()
    }

    public List collectInitialStates() {
        def newStates = []
        this.fsmConfig.transitionList
                .findAll{ it.from.isStarting && !(it.to.isFinal && it.by.isEmptySymbol) }
                .collect { it.from }
                .each { newStates << it}
        this.fsmConfig.transitionList
                .findAll{ it.from.isStarting && it.to.isFinal && it.by.isEmptySymbol }
                .collect {it.to }
                .each { newStates << it}
        return newStates
    }
}
