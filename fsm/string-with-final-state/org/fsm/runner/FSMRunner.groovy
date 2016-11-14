package org.fsm.runner

import com.sun.corba.se.spi.orbutil.fsm.FSM
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
        List <Tuple2> exits = []
        List<FSMachine> machineList = []
        this.fsmConfig.stateList.findAll { it.isStarting }.each { machineList << ([it, this.fsmConfig] as FSMachine) }

        machineList.findAll { it.currentState.isFinal }.each { exits << ([true, -1] as Tuple2)}

        machineList.each { println it.currentState }

        inputString.eachWithIndex { aChar, charIdx ->
            def newStates = tickMachine(machineList, aChar).collect { TransitionRule tr -> tr.to }
            println newStates
            println "finals: ${newStates.findAll { it.isFinal }}"
            newStates.findAll { it.isFinal }.each {
                exits << ([true, charIdx] as Tuple2)
            }
            println exits

            machineList.clear()
            newStates.each { it ->
                machineList << ([it, this.fsmConfig] as FSMachine)
            }
            println '----'
        }

        if (exits.size()) {
            println exits
            println exits.max { Tuple2 t -> t.second }
        } else {
            println "[false, null]"
        }

    }


    public  List tickMachine(currentMachineList, aChar) {
        def newStates = []
        currentMachineList.each { FSMachine m -> newStates << m.feedChar(aChar) }
        return newStates.flatten()
    }
}
