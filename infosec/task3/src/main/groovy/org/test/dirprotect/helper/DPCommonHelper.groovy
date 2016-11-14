package org.test.dirprotect.helper
import java.security.*

/**
 * Created by vslepukhin on 10/11/2016.
 */
abstract class DPCommonHelper {
    static def generateHash(String username, String password) {
        def sha1 = MessageDigest.getInstance("SHA1")
        byte[] digest  = sha1.digest("${username}${password}".getBytes())
        return new BigInteger(1, digest).toString(16).take(7)
    }
}
