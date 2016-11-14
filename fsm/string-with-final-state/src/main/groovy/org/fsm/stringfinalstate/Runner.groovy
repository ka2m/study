package org.fsm.stringfinalstate

import org.fsm.fsmlib.entity.TransitionRule
import org.fsm.fsmlib.machine.FSMachine
import org.fsm.fsmlib.runner.FSMRunner

/**
 * Created by vslepukhin on 18/09/2016.
 */
class Runner extends FSMRunner {

    public Runner(configFile) {
        super(configFile)
    }


    public void run(inputString, startNum) {
        def resLine = inputString.drop(startNum)
        println "resLine: ${resLine}"

        Tuple2 exit = new Tuple2(false, null)
        List<FSMachine> machineList = []
        this.fsmConfig.stateList.findAll { it.isStarting }.each { machineList << ([it, this.fsmConfig] as FSMachine) }

        if (machineList.find{ it.currentState.isFinal } != null) {
            exit = [true, 0] as Tuple2
        }

        machineList.each { println it.currentState }

        resLine.eachWithIndex { aChar, charIdx ->
            def newStates = tickMachine(machineList, aChar).collect { TransitionRule tr -> tr.to }
            println newStates
            println "finals: ${newStates.findAll { it.isFinal }}"
            if (newStates.count { it.isFinal } != 0) {
                exit = ([true, charIdx + 1] as Tuple2)
            }

            machineList.clear()
            newStates.each { it ->
                machineList << ([it, this.fsmConfig] as FSMachine)
            }
            println '----'
        }

        println exit
        println "======"

    }


    public  List tickMachine(currentMachineList, aChar) {
        def newStates = []
        currentMachineList.each { FSMachine m -> newStates << m.feedChar(aChar) }
        return newStates.flatten()
    }
}
