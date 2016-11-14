package org.fsm.token.recognition

import groovy.json.JsonSlurper
import org.fsm.token.fsmrunner.TokenRunner

/**
 * Created by vslepukhin on 14/11/2016.
 */
class TokenSplitter {

    def tokenRunners = []

    public TokenSplitter(String fsmGlobalConfig) {
        def slurper = new JsonSlurper()
        def globalCfg = slurper.parseText(new File(fsmGlobalConfig).text)
        def configLocation = globalCfg.relativeConfigFilePath

        globalCfg.configs.each { c ->
            tokenRunners << new TokenRunner("${configLocation}/${c.fileName}.json" as String,
                                            c.tokenClassName as String,
                                            c.priority as int,
                                            true)
        }
    }

    public split(String source) {
        def finalResults = []
        def fail = false
        while (source.length() != 0) {
            def positive = []
            this.tokenRunners.each { TokenRunner tr ->
                Tuple2 res = tr.readToken(source)
                if (res.first)
                    positive << ["count" : res.second, "tokenClass": tr.tokenClass, "priority": tr.priority]
            }

            if (positive.size() == 0) {
                println "Syntax error starting from ${source.take(20)}"
                fail = true
                break
            }

            positive = positive.sort{ it.count }.reverse().sort{ it.priority }

            def finalResult = [positive[0].tokenClass, source.take(positive[0].count)] as Tuple2

            finalResults << finalResult

            source = source.drop(positive[0].count)
        }

        if (!fail) {
            finalResults.each { println it }
        }
    }
}
