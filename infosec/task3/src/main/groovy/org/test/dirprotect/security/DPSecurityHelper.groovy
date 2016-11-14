package org.test.dirprotect.security

import javax.crypto.Cipher
import javax.crypto.spec.SecretKeySpec

/**
 * Created by vslepukhin on 10/11/2016.
 */
abstract class DPSecurityHelper {
    private static final String ALGORITHM = "AES";
    private static final String TRANSFORMATION = "AES";

    static def encryptFile(File file, String hash) {
        println "Encrtypting: ${file.getAbsolutePath()}"
        cryptFunction(file, hash, Cipher.ENCRYPT_MODE)
    }

    static def decrtyptFile(File file, String hash) {
        println "Decrypting: ${file.getAbsolutePath()}"
        cryptFunction(file, hash, Cipher.DECRYPT_MODE)
    }

    static def cryptFunction(File file, String hash, int mode) {
        def secretKey = new SecretKeySpec(hash.getBytes("UTF-16"), ALGORITHM);
        def cipher = Cipher.getInstance(TRANSFORMATION);
        cipher.init(mode, secretKey);

        def inputStream = new FileInputStream(file);
        byte[] inputBytes = new byte[(int) file.length()];
        inputStream.read(inputBytes);
        inputStream.close();

        def cryptedFile = new File(file.getAbsolutePath())
        file.delete()

        byte[] outputBytes = cipher.doFinal(inputBytes);
        FileOutputStream outputStream = new FileOutputStream(cryptedFile);
        outputStream.write(outputBytes);


        outputStream.close();
    }
}
