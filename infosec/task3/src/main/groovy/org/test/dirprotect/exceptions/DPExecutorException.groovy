package org.test.dirprotect.exceptions

/**
 * Created by vslepukhin on 10/11/2016.
 */
class DPExecutorException extends Exception {
    //Parameterless Constructor
    public DPExecutorException() {}

    //Constructor that accepts a message
    public DPExecutorException(String message) {
        super(message);
    }
}
