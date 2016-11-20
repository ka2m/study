package org.fsm.fsmlib.entity
/**
 * Created by vslepukhin on 18/09/2016.
 */
class Transition {
    State from
    State to
    Alpha by

    Transition() {
    }

    Transition(State from, State to, Alpha by) {
        this.from = from
        this.to = to
        this.by = by
    }

    boolean equals(o) {
        if (this.is(o)) return true
        if (getClass() != o.class) return false

        Transition that = (Transition) o

        if (by != that.by) return false
        if (from != that.from) return false
        if (to != that.to) return false

        return true
    }

    int hashCode() {
        int result
        result = from.hashCode()
        result = 31 * result + to.hashCode()
        result = 31 * result + by.hashCode()
        return result
    }

    @Override
    public String toString() {
        return "Transition{" +
                "from=" + from +
                ", to=" + to +
                ", by=" + by +
                '}';
    }
}
