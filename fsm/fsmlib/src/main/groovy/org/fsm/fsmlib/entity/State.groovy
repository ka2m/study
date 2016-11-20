package org.fsm.fsmlib.entity
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

    @Override
    boolean equals(o) {
        if (this.is(o)) return true
        if (getClass() != o.class) return false

        State state = (State) o

        if (isFinal != state.isFinal) return false
        if (isStarting != state.isStarting) return false
        if (name != state.name) return false

        return true
    }

    @Override
    int hashCode() {
        int result
        result = (name != null ? name.hashCode() : 0)
        result = 31 * result + (isStarting ? 1 : 0)
        result = 31 * result + (isFinal ? 1 : 0)
        return result
    }
}
