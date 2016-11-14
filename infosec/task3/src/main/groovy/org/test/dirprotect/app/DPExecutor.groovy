package org.test.dirprotect.app

import org.test.dirprotect.exceptions.DPExecutorException
import org.test.dirprotect.security.DPSecurityHelper

import static groovy.io.FileType.FILES
import org.test.dirprotect.vault.DPUser

/**
 * Created by vslepukhin on 10/11/2016.
 */
abstract class DPExecutor {
    static def encrypt(DPUser user) {
        new File(user.homeDir).traverse(type: FILES) { userfile ->
            DPSecurityHelper.encryptFile(userfile, user.hash)
        }

    }

    static def decrypt(DPUser user) {
        new File(user.homeDir).traverse(type: FILES) { userfile ->
            DPSecurityHelper.decrtyptFile(userfile, user.hash)
        }
    }

    static def createUserDirectory(DPUser user) {
        def result = new File(user.homeDir).mkdirs()
        if (!result) {
            throw new DPExecutorException("Unable to create home directory")
        }
    }

    static def createUserDirectory(String path) {
        def result = new File(path).mkdirs()
        if (!result) {
            throw new DPExecutorException("Unable to create home directory")
        }
    }

    static def deleteUserDirectory(DPUser user) {
        def result = new File(user.homeDir).deleteDir()
        if (!result) {
            throw new DPExecutorException("Unable to remove home directory")
        }
    }
}
