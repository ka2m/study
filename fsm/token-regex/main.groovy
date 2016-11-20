import groovy.json.JsonSlurper
import org.fsm.token.fsmrunner.TokenRunner
import org.fsm.token.recognition.TokenSplitter

def testNumberFSM(regex) {
    def fsmRunner = new TokenRunner(regex, "number", 1, false)
    def tests = ["+123.5e-2",
                 "+123.5e-21",
                 "+123.5e-",
                 "+123.5e",
                 "+123.5",
                 "+123.",
                 "+123.e2",
                 "+123",
                 "-123",
                 "123",
                 ".5",
                 "3e7",
                 "+3e7",
                 "1e-2",
                 "0.5",
                 ".5e2",
                 ".e2",
                 "+.e82",
                 "+.",
                 ".",
                 ".+",
                 "+e8",
                 "-.e8",
                 "-.8"]
    tests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }
}

def testKeywordFSM(regex) {
    println "========================"
    TokenRunner fsmRunner = new TokenRunner(regex, "keyword", 1, false)
    def positiveTests = ["while", "do", "if", "then", "else", "begin", "end"]
    def negativeTests = ["whil", "od", "blabl", "tenh", "superstring", "notvalid", "eee"]

    positiveTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }

    negativeTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }
    println "========================"
}

def testOpsFSM(regex) {
    println "========================"
    def fsmRunner = new TokenRunner(regex, "op")
    def positiveTests = [":=", "*", "-", "/", "+"]
    def negativeTests= ["=",":", "(", "while", "123.5e-", ")"]
    positiveTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }

    negativeTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }
    println "========================"
}

def testIdFSM(regex) {
    println "========================"
    TokenRunner fsmRunner = new TokenRunner(regex, "id", 1, false)
    def positiveTests = ["a", "bcd", "a1", "hey123", "a1b2c3"]
    def negativeTests= ["1", "123", "()()()"]
    positiveTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }

    negativeTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }
    println "========================"
}

def testEmptyFSM(regex) {
    println "========================"
    def fsmRunner = new TokenRunner(regex, "id", 1, false)
    def positiveTests = [" ", "  ", "   ", """
"""]
    def negativeTests = ["1", "abcd", ";", ""]
    positiveTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }

    negativeTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }
    println "========================"
}

def testOpenParFSM(regex) {
    println "========================"
    def fsmRunner = new TokenRunner(regex, "id", 1, false)
    def positiveTests = [")"]
    def negativeTests = ["1", "abcd", ";", "    "]
    positiveTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }

    negativeTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }
    println "========================"
}

def testCloseParFSM(regex) {
    println "========================"
    def fsmRunner = new TokenRunner(regex, "id", 1, false)
    def positiveTests = [")"]
    def negativeTests = ["1", "abcd", ";", "    "]
    positiveTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }

    negativeTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }
    println "========================"
}

def testSemiColonFSM(regex) {
    println "========================"
    def fsmRunner = new TokenRunner(regex, "id", 1, false)
    def positiveTests = [";"]
    def negativeTests = ["1", "abcd", ";", "    "]
    positiveTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }

    negativeTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }
    println "========================"

}

def runTests() {
    def slurper = new JsonSlurper()
    def regexCfg = slurper.parseText(new File("src/main/resources/regex.json").text)
    testNumberFSM(regexCfg.find { it.tokenName == "number" }.regex)
    testKeywordFSM(regexCfg.find { it.tokenName == "kw" }.regex)
    testOpsFSM(regexCfg.find { it.tokenName == "op" }.regex)
    testIdFSM(regexCfg.find { it.tokenName == "id" }.regex)
    testCloseParFSM(regexCfg.find { it.tokenName == "closeParenthesis" }.regex)
    testOpenParFSM(regexCfg.find { it.tokenName == "openParenthesis" }.regex)
    testSemiColonFSM(regexCfg.find { it.tokenName == "semicolon" }.regex)
    testEmptyFSM(regexCfg.find { it.tokenName == "delim" }.regex)
}

//runTests()
def ts = new TokenSplitter("src/main/resources/regex.json")
ts.split(new File("exampleProgram.code").text)