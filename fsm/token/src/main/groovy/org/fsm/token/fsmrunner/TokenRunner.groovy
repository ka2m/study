package org.fsm.token.fsmrunner

import org.fsm.fsmlib.entity.TransitionRule
import org.fsm.fsmlib.machine.FSMachine
import org.fsm.fsmlib.runner.FSMRunner

/**
 * Created by vslepukhin on 14/11/2016.
 */
class TokenRunner extends FSMRunner {

    String tokenClass
    int priority
    boolean quietMode

    public TokenRunner(String configFile, String tokenClass, int priority=0, boolean quiet=false) {
        super(configFile, quiet)
        this.quietMode = quiet
        this.tokenClass = tokenClass
        this.priority = priority
    }

    public Tuple2 readToken(String inputString) {
        List<FSMachine> machineList = []
        def exit = ([false, 0] as Tuple2)
        this.fsmConfig.stateList.findAll { it.isStarting }.each { machineList << ([it, this.fsmConfig] as FSMachine) }
        try {
            inputString.eachWithIndex { aChar, idx ->
                def newStates = tickMachine(machineList, aChar).collect { TransitionRule tr -> tr.to }

                if (newStates.count { it.isFinal } != 0) {
                    exit = ([true, idx + 1] as Tuple2)
                }

                machineList.clear()
                newStates.each { it ->
                    machineList << ([it, this.fsmConfig] as FSMachine)
                }
            }
        } catch (Exception ex) {
            if (!quietMode)
                println ex.toString()
        }
        if (!quietMode)
            println "This string: ${inputString} ------ ${(exit.first) ? "" : "NOT"} valid for this FSM"
        return exit
    }
}
