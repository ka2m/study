package org.test.dirprotect.vault

import com.gmongo.GMongo
import org.test.dirprotect.exceptions.DPVaultException
import org.test.dirprotect.helper.DPCommonHelper

import java.security.MessageDigest

/**
 * Created by vslepukhin on 10/11/2016.
 */
class DPVaultConnector {
    private final def dbHost = "0.0.0.0"
    private final def dbPort = "27017"
    private def connector;

    def DPVaultConnector() {
        println 'Connecting to secure vault'
        this.connector = new GMongo("${dbHost}:${dbPort}")
    }

    def register(String username, String password, String homeDir) {
        def db = this.connector.getDB("dirProtect")

        if (db.dirProtect.count(user: username)) {
            throw new DPVaultException("DPUser with same name already exists")
        }

        if (!username.length()) {
            throw new DPVaultException("Empty passwords are not allowed")
        }

        if (db.dirProtect.count(home: homeDir)) {
            throw new DPVaultException("DPUser with same home directory already exists")
        }

        MessageDigest sha1 = MessageDigest.getInstance("SHA1")
        byte[] digest  = sha1.digest(password.getBytes())

        db.dirProtect << ["user"    : username,
                          "password": new  BigInteger(1, digest).toString(16),
                          "home"    : homeDir,
                          "hash"    : DPCommonHelper.generateHash(username, password),
                          "loggedIn": false]
    }

    def login(String username, String password) {
        def db = this.connector.getDB("dirProtect")
        checkUsername(db, username)
        checkPassword(db, username, password)

        db.dirProtect.update([user: username], [$set: [loggedIn: true]])

        def u = new DPUser(username,
                db.dirProtect.findOne(user: username).home,
                db.dirProtect.findOne(user: username).hash)

        return u
    }

    def logout(String username) {
        def db = this.connector.getDB("dirProtect")
        checkUsername(db, username)

        if (!db.dirProtect.findOne(user: username).loggedIn) {
            throw new DPVaultException("User not logged in")
        }
        db.dirProtect.update([user: username], [$set: [loggedIn: false]])

        def u = new DPUser(username,
                db.dirProtect.findOne(user: username).home,
                db.dirProtect.findOne(user: username).hash)

        return u
    }

    def delete(String username, String password) {
        def db = this.connector.getDB("dirProtect")

        checkUsername(db, username)
        checkPassword(db, username, password)

        def u = new DPUser(username,
                db.dirProtect.findOne(user: username).home,
                db.dirProtect.findOne(user: username).hash)

        db.dirProtect.remove(user: username)
        return u
    }

    static private def checkUsername(db, username) {
        println 'Checking user'
        if (!db.dirProtect.count(user: username)) {
            throw new DPVaultException("No such user")
        }
    }

    static private def checkPassword(db, username, password) {
        println 'Checking password'
        MessageDigest sha1 = MessageDigest.getInstance("SHA1")
        byte[] digest  = sha1.digest(password.getBytes())
        def incStr = new  BigInteger(1, digest).toString(16)

        if (db.dirProtect.findOne(user: username).password != incStr) {
            throw new DPVaultException("Wrong password")
        }
    }
}
