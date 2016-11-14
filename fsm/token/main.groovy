import org.fsm.token.fsmrunner.TokenRunner
import org.fsm.token.recognition.TokenSplitter

def testNumberFSM() {
    def fsmRunner = new TokenRunner("src/main/resources/realNumber.json", "number")
    def tests = ["+123.5e-2",
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

def testKeywordFSM() {
    def fsmRunner = new TokenRunner("src/main/resources/keyword.json", "keyword")
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
}

def testOpsFSM() {
    def fsmRunner = new TokenRunner("src/main/resources/operations.json", "op")
    def positiveTests = [":=", "*", "-", "/", "+"]
    def negativeTests= ["=",":", "(", "while", "123.5e-", ")", "++++"]
    positiveTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }

    negativeTests.each { test ->
        Tuple2 res = fsmRunner.readToken(test)
        println res
    }
}

def testIdFSM() {
    def fsmRunner = new TokenRunner("src/main/resources/id.json", "id")
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
}

def testEmptyFSM() {
    def fsmRunner = new TokenRunner("src/main/resources/emptySpace.json", "id")
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
}

def testOpenParFSM() {
    def fsmRunner = new TokenRunner("src/main/resources/openParanthesis.json", "id")
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
}

def testCloseParFSM() {
    def fsmRunner = new TokenRunner("src/main/resources/closeParanthesis.json", "id")
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
}

def testSemiColonFSM() {
    def fsmRunner = new TokenRunner("src/main/resources/semicolon.json", "id")
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
}

def runTests() {
    testNumberFSM()
    testKeywordFSM()
    testOpsFSM()
    testIdFSM()
    testCloseParFSM()
    testOpenParFSM()
    testSemiColonFSM()
    testEmptyFSM()
}

//runTests()
def ts = new TokenSplitter("src/main/resources/globalConfig.json")
//ts.split("c:=34/2.0")
//ts.split("1bc")
ts.split(new File("exampleProgram.code").text)