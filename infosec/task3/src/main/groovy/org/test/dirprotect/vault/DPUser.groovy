package org.test.dirprotect.vault

/**
 * Created by vslepukhin on 10/11/2016.
 */
class DPUser {
    String username
    String homeDir
    String hash

    def DPUser() {
    }

    def DPUser(String username, String homeDir, String hash) {
        this.username = username
        this.homeDir = homeDir
        this.hash = hash
    }
}
