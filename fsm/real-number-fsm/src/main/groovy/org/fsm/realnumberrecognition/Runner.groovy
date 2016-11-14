package org.fsm.realnumberrecognition

import org.fsm.fsmlib.entity.TransitionRule
import org.fsm.fsmlib.machine.FSMachine
import org.fsm.fsmlib.runner.FSMRunner

/**
 * Created by vslepukhin on 20/09/2016.
 */
class Runner extends FSMRunner {

    public Runner(String configFile) {
        super(configFile)
    }

    @Override
    public void run(String inputString) {
        List<FSMachine> machineList = []
        this.fsmConfig.stateList.findAll { it.isStarting }.each { machineList << ([it, this.fsmConfig] as FSMachine) }

        inputString.each { aChar ->
            def newStates = tickMachine(machineList, aChar).collect { TransitionRule tr -> tr.to }

            machineList.clear()
            newStates.each { it ->
                machineList << ([it, this.fsmConfig] as FSMachine)
            }
        }

        if (machineList.find { it.currentState.isFinal })
            println "This string ${inputString} is valid for this FSM"
        else
            println "This string ${inputString} is NOT valid for this FSM"
    }

}
