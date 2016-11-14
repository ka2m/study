package org.test.dirprotect.exceptions

/**
 * Created by vslepukhin on 10/11/2016.
 */
class DPVaultException extends Exception {
        //Parameterless Constructor
        public DPVaultException() {}

        //Constructor that accepts a message
        public DPVaultException(String message) {
            super(message);
        }
}

