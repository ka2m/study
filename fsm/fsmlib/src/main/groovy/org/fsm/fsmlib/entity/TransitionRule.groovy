package org.fsm.fsmlib.entity
/**
 * Created by vslepukhin on 18/09/2016.
 */
class TransitionRule {
    State to
    Alpha alpha

    public TransitionRule(State state, Alpha alpha) {
        this.to = state
        this.alpha = alpha
    }
}
