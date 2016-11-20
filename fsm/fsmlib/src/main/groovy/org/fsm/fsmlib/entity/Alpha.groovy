package org.fsm.fsmlib.entity
/**
 * Created by vslepukhin on 18/09/2016.
 */
class Alpha {
    String name
    String validChars
    boolean isEmptySymbol

    Alpha(String name, validChars) {
        this.name = name
        this.validChars = validChars
        this.isEmptySymbol = false
    }

    Alpha(String name) {
        this.name = name
        this.validChars = ""
        this.isEmptySymbol = true
    }

    Alpha(String name, String validChars, boolean isEmptySymbol) {
        this.name = name
        this.validChars = validChars
        this.isEmptySymbol = isEmptySymbol
    }

    @Override
    public String toString() {
        if (isEmptySymbol)
            return "${name} with (empty)"
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
