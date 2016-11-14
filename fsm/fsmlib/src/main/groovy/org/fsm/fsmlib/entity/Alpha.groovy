package org.fsm.fsmlib.entity
/**
 * Created by vslepukhin on 18/09/2016.
 */
class Alpha {
    String name
    String validChars

    Alpha(name, validChars) {
        this.name = name
        this.validChars = validChars
    }


    @Override
    public String toString() {
        return "${name} with ${validChars}"
    }

    @Override
    public boolean equals(Object other) {
        if (other instanceof Alpha) {
            return this.name == other.name
        }
        return false
    }
}
