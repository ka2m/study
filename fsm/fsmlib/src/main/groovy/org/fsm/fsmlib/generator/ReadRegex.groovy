package org.fsm.fsmlib.generator

import org.fsm.fsmlib.machine.FSMTransform
import org.fsm.fsmlib.generator.helper.RegexSymbol
import org.fsm.fsmlib.machine.FSMConfig

/**
 * Created by vslepukhin on 17/11/2016.
 */
class ReadRegex {
    public ReadRegex() {
    }

    static FSMConfig readRegexString(String str) {
        def strSize = str.length()
        def buf = ""

        def actionItems = []

        for (int i = 0; i < strSize; i++) {
            buf += str[i];
            if (buf == "~w") {
                actionItems << FSMTransform.generateBasicFSM(RegexSymbol.AnySymbol)
                buf = ""
            } else if (buf == "~(") {
                actionItems << RegexSymbol.OpenParenthesis
                buf = ""
            } else if (buf == "~)") {
                actionItems << RegexSymbol.CloseParenthesis
                buf = ""
            } else if (buf == "~d") {
                actionItems << FSMTransform.generateBasicFSM(RegexSymbol.AnyNumber)
                buf = ""
            } else if (buf == "~+") {
                actionItems << RegexSymbol.Unite
                buf = ""
            } else if (buf == "~*") {
                actionItems << RegexSymbol.Iterate
                buf = ""
            } else if (buf != "~") {
                actionItems << FSMTransform.generateBasicFSM(RegexSymbol.ExactSymbol, buf)
                buf = ""
            }
        }

        while (actionItems.size() != 1) {
            while (actionItems.find { it == RegexSymbol.OpenParenthesis } != null) {
                int idxLastOpen = actionItems.findLastIndexOf { it == RegexSymbol.OpenParenthesis }
                int idxFirstClose = actionItems.findIndexOf(idxLastOpen, { it == RegexSymbol.CloseParenthesis })
                if (idxFirstClose != -1 && idxLastOpen != -1) {
                    FSMTransform.reduceList(actionItems.subList(idxLastOpen, idxFirstClose + 1), true)
                    actionItems.removeIf { it == null }
                }
            }

            FSMTransform.reduceList(actionItems, false)
        }
        return actionItems[0] as FSMConfig
    }

}
