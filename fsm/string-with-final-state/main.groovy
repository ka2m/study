import org.fsm.stringfinalstate.Runner

/**
 * Created by vslepukhin on 18/09/2016.
 */

def fsmRunner = new Runner("definition.json")
fsmRunner.run('abcca', 1)
//fsmRunner.run('babac', 2)