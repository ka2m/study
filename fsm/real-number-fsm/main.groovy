import org.fsm.realnumberrecognition.Runner

/**
 * Created by vslepukhin on 18/09/2016.
 */

def fsmRunner = new Runner("definition.json")
fsmRunner.run("+123.5e-2")
fsmRunner.run("+123.5e-2")
fsmRunner.run("+123.5e-")
fsmRunner.run("+123.5e")
fsmRunner.run("+123.5")
fsmRunner.run("+123.")
fsmRunner.run("+123.e2")
fsmRunner.run("+123")
fsmRunner.run("-123")
fsmRunner.run("123")
fsmRunner.run(".5")
fsmRunner.run("3e7")
fsmRunner.run("+3e7")
fsmRunner.run("1e-2")
fsmRunner.run("0.5")
fsmRunner.run(".5e2")
fsmRunner.run(".e2")
fsmRunner.run("+.e82")
fsmRunner.run("+.")
fsmRunner.run(".")
fsmRunner.run(".+")
fsmRunner.run("+e8")
fsmRunner.run("-.e8")
fsmRunner.run("-.8")