package org.fsm.machine

import de.vandermeer.asciitable.v2.RenderedTable
import de.vandermeer.asciitable.v2.V2_AsciiTable
import de.vandermeer.asciitable.v2.render.V2_AsciiTableRenderer
import de.vandermeer.asciitable.v2.render.WidthAbsoluteEven
import de.vandermeer.asciitable.v2.themes.V2_E_TableThemes
import org.fsm.entity.Alphabet
import org.fsm.entity.State
import org.fsm.entity.Transition

/**
 * Created by vslepukhin on 18/09/2016.
 */
class FSMConfig {
    Alphabet alphabet
    List<State> stateList = []
    List<Transition> transitionList

    public FSMConfig(config) {
        this.alphabet = new Alphabet(config.alphabet)
        this.transitionList = []
        config.states.each { stateList << ([it.name, it.starting, it.final] as State)}
        config.transitions.each { t ->
            def state = stateList.find { s -> s.name == t.from }
            def moves = []
            t.to.each { toState ->
                moves << ["state": stateList.find { s -> s.name == toState.state },
                          "alpha": alphabet.alphaList.find { a -> a.name == toState.alpha } ]
            }

            this.transitionList << ([state, moves] as Transition)
        }

    }


    public describe() {
        println "This FSM has the following alphabet:"
        this.alphabet.alphaList.each {println it}

        println "\nTotal allowed charcter list: ${this.alphabet.allAllowedChars}"

        println "\nThis FSM has the following states with names:"
        this.stateList.each { print "${it.name} " }

        println "\n\nInitial (starting) states are:"
        this.stateList.findAll { it.isStarting}.each { s -> print "${s.name} " }

        println "\n\nFinal states are:"
        this.stateList.findAll { it.isFinal}.each { s -> print "${s.name} " }

        println "\n\n"

        V2_AsciiTable at = new V2_AsciiTable()
        at.addRule()
        at.addRow('', *this.alphabet.alphaList.collect { it.name })
        V2_AsciiTableRenderer rend = new V2_AsciiTableRenderer();
        rend.setTheme(V2_E_TableThemes.UTF_LIGHT.get())
        rend.setWidth(new WidthAbsoluteEven(76))



        this.transitionList.sort { it.from.name }.sort { !it.from.isStarting }.each {  s ->
            at.addRule()
            def displayRow = []
            displayRow << s.from.transitionTableStateDescription()

            this.alphabet.alphaList.each { a->
                def search = s.possibleMoves.findAll { a == it.alpha }
                if (!search.size()) {
                    displayRow << "x"
                }
                else {
                    search.each { fs ->
                        displayRow << fs.to.name
                    }
                }
            }
            at.addRow(*displayRow)
        }
        at.addRule()
        RenderedTable rt = rend.render(at)
        println rt



    }
}
