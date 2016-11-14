package org.fsm.runner

import groovy.json.JsonSlurper
import org.fsm.entity.TransitionRule
import org.fsm.machine.FSMConfig
import org.fsm.machine.FSMachine

/**
 * Created by vslepukhin on 18/09/2016.
 */
class FSMRunner {
    FSMConfig fsmConfig

    public FSMRunner(configFile) {
        def data = new JsonSlurper().parse(new File(configFile))
        this.fsmConfig = new FSMConfig(data)
        this.fsmConfig.describe()
    }

    public void run(inputString) {
        List<FSMachine> machineList = []
        this.fsmConfig.stateList.findAll { it.isStarting }.each { machineList << ([it, this.fsmConfig] as FSMachine) }

        inputString.each { aChar ->
            def newStates = tickMachine(machineList, aChar).collect { TransitionRule tr -> tr.to }

            machineList.clear()
            newStates.each { it ->
                machineList << ([it, this.fsmConfig] as FSMachine)
            }
            machineList.each { print "${it.currentState} " }
        }

        if (machineList.find { it.currentState.isFinal })
            println "\nThis string ${inputString} is valid for this FSM"
        else
            println "\nThis string ${inputString} is NOT valid for this FSM"
    }


    public  List tickMachine(currentMachineList, aChar) {
        def newStates = []
        currentMachineList.each { FSMachine m -> newStates << m.feedChar(aChar) }
        return newStates.flatten().unique()
    }
}
