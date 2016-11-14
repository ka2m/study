package org.fsm.fsmlib.entity
/**
 * Created by vslepukhin on 18/09/2016.
 */
class Transition {
    State from
    List<TransitionRule> possibleMoves = []

    public Transition(origin, movesList) {
        this.from  = origin
        movesList.each { this.possibleMoves << ([it.state, it.alpha] as TransitionRule) }
    }
}
