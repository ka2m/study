package org.test.dirprotect.app

import org.test.dirprotect.exceptions.DPExecutorException
import org.test.dirprotect.vault.DPVaultConnector
import org.test.dirprotect.vault.DPUser
import org.test.dirprotect.exceptions.DPVaultException

/**
 * Created by vslepukhin on 10/11/2016.
 */
class DPRunner {
    static void main(String[] args) {
        println "DirProtect app"

        def cli = new CliBuilder(usage: 'dirprotect -<h|r|l|e|d>')
        // Create the list of options.
        cli.with {
            h longOpt: 'help', 'Show usage information'
            r longOpt: 'register', 'Add a user and create a directory"'
            l longOpt: 'login', 'Decrypt directory files'
            e longOpt: 'exit', 'Encrypt directory files'
            d longOpt: 'delete', 'Remove recording about the user and oblitirate the directory'
        }

        def options = cli.parse args

        if (!options) {
            cli.usage()
            return
        }

        if (options.h) {
            cli.usage()
            return
        }

        def username = ""
        def password = ""
        def homeDirectory = ""

        if (options.r || options.l || options.e ||  options.d) {
            username = System.console().readLine 'Username: '
        }

        if (options.r) {
            password = System.console().readPassword 'Password: '
            def repeat = System.console().readPassword 'Repeat password: '
            if (password != repeat) {
                println 'Paswords don\'t match'
                return
            }
            def _hd = System.console().readLine 'Home directory (leave empty to use ./<username>): '
            if (!_hd.length()) {
                _hd = "./${username}"
            }
            homeDirectory = new File(_hd).getAbsolutePath()
        }
        else if (options.l) {
            password = System.console().readPassword 'Password: '
        }
        else if (options.d) {
            password = System.console().readPassword 'Password: '
        }
        else if (!options.e) {
            cli.usage()
            return
        }

        try {
            def connector = new DPVaultConnector();
            if (options.r) {
                println 'Creating new user'
                connector.register(username, password as String, homeDirectory)
                DPExecutor.createUserDirectory(homeDirectory)
                println 'Successfully created user. You can now login with your username'
            }
            else if (options.l) {
                println 'Logging in'
                def u = connector.login(username, password as String) as DPUser
                DPExecutor.decrypt(u)
                println "Logged in. You can explore your files at ${u.homeDir}"
            }
            else if (options.e) {
                println 'Logging out'
                def u = connector.logout(username) as DPUser
                DPExecutor.encrypt(u)
                println "Logged out. Files encrypted in: ${u.homeDir}"
            }
            else if (options.d) {
                println 'Deleting user'
                def u = connector.delete(username, password as String) as DPUser
                DPExecutor.deleteUserDirectory(u)
                //remove stuff
                println "Deleted account and user data"
            }
        } catch (DPVaultException ex) {
            println "Problem during vault operation: ${ex.message}"
        } catch (DPExecutorException ex) {
            println "Problem during execution operation: ${ex.message}"
        } catch (Exception ex) {
            println "Unexpected exception: ${ex.message}"
            ex.printStackTrace()
        }
    }
}
