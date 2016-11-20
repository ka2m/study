import org.fsm.fsmlib.entity.Transition
import org.fsm.fsmlib.generator.ReadRegex
import org.fsm.fsmlib.machine.FSMachine
import org.fsm.fsmlib.runner.FSMRunner
import org.fsm.fsmlib.entity.State

def rr = new ReadRegex()
//rr.readRegexString("\\w\\(\\w\\*\\d\\*\\)\\*")
//FSMConfig fsm = rr.readRegexString

FSMRunner fsmr = new FSMRunner("a~*b~*", false)

List<FSMachine> machineList = []
def exit = ([false, 0] as Tuple2)

fsmr.collectInitialStates().each { machineList << ([it, fsmr.fsmConfig] as FSMachine) }



"aaaabbb".eachWithIndex { aChar, idx ->
    def newStates = fsmr.tickMachine(machineList, aChar).collect { Transition t -> t.to }

    if (newStates.count { it.isFinal } != 0) {
        exit = ([true, idx + 1] as Tuple2)
    }

    machineList.clear()
    newStates.each { State it ->
        machineList << ([it, fsmr.fsmConfig] as FSMachine) }


}



println exit