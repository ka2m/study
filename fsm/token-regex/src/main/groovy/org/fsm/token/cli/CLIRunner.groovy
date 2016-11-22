package org.fsm.token.cli

import org.fsm.token.fsmrunner.TokenRunner
import org.fsm.token.recognition.TokenSplitter

/**
 * Created by vslepukhin on 22/11/2016.
 */
class CLIRunner {
    private static void printHelp() {
        println """
            Vlad Regex Parser

            Available commands:

            %w - any english symbol
            %d - any digit
            | - or (unite)
            %* - iterate (zero or more)
            %+ - positive iterate (one or more)
            %? - iterate once (zero or exactly one)
            %( %) - parenthesis must be escaped
            no special symbol for concatenation

            Regex Mode:
            CLI utility returns initial length of string and
            Tuple of 2 [<true|false>, <subStringLength>], where

            - <true|false> - does the test string match regex
            - <subStringLength> - how many characters from test string has been recognized

            Program Parse Mode:
            CLI utility returns list of tokens line by line with their classes and substrings
            as per configuration in -c option

""".stripIndent()

    }
    static void main(String... args) {

        def cli = new CliBuilder(usage: 'token-regex <-h|-r|-p programFile -c configFile>')
        // Create the list of options.
        cli.with {
            h longOpt: 'help', 'Show usage information'
            r longOpt: 'regex', 'match regex'
            p args:1, longOpt: 'program', 'program to parse'
            c args:1, longOpt: 'config', 'regex config for program'
        }

        def options = cli.parse args

        if (!options) {
            cli.usage()
            printHelp()
            return
        }

        if (options.h) {
            cli.usage()
            printHelp()
            return
        }
        if (options.r) {
            printHelp()
            def myRegex = System.console().readLine("Regex: ")
            def testString = System.console().readLine("Test string: ")
            def res = new TokenRunner(myRegex, "number", 1, true).readToken(testString)
            println "Test length: ${testString.length()}"
            println res
        } else {
            printHelp()
            def ts = new TokenSplitter(options.c)
            ts.split(new File(options.p).text)
        }
    }
}

