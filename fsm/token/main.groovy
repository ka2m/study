import org.fsm.token.fsmrunner.TokenRunner

def testNumberFSM() {
    def fsmRunner = new TokenRunner("src/main/resources/realNumber.json", "number", false)
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
    def fsmRunner = new TokenRunner("src/main/resources/keyword.json", "keyword", false)
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

def testOps() {
    def fsmRunner = new TokenRunner("src/main/resources/operations.json", "op", false)
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

def testId() {
    def fsmRunner = new TokenRunner("src/main/resources/id.json", "id", false)
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

def runTests() {
    testNumberFSM()
    testKeywordFSM()
    testOps()
    testId()
}

testKeywordFSM()
testId()
