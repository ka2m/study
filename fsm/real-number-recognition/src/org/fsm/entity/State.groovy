package org.fsm.entity
/**
 * Created by vslepukhin on 18/09/2016.
 */
class State {
    String name
    boolean isStarting
    boolean isFinal

    public State(name, isStarting, isFinal) {
        this.name = name
        this.isStarting = isStarting
        this.isFinal = isFinal
    }

    @Override
    public String toString() {
        return "${name}${isStarting ? ':start' : ''}${isFinal ? ':fin' : ''}"
    }

    public String transitionTableStateDescription() {
        def statePrintName = this.name
        if (this.isFinal) statePrintName = "(${statePrintName})"
        if (this.isStarting) statePrintName  = "->${statePrintName}"

        return statePrintName
    }
}
