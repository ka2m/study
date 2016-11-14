import org.fsm.runner.FSMRunner

/**
 * Created by vslepukhin on 18/09/2016.
 */

def fsmRunner = new FSMRunner("definition.json")
fsmRunner.run('abcca')