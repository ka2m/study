def gcd(int i, int j) {
    if (Math.min(i, j) == 0) return Math.max(i, j)
    else return gcd(Math.min(i,j), Math.abs(i - j))
}

def encryptAlpha(String alphabet, String x, int key1, int key2) {
    def pos = alphabet.indexOf(x)
    if (pos != -1) {
        def alphaSize = alphabet.length()
        def newPos = (pos * key1 + key2) % alphaSize
        if (newPos >= alphaSize) {
            newPos -= alphaSize
        }
        return alphabet[newPos]
    }
    return x
}

def decryptAlpha(String alphabet, String x, int key1, int key2) {
    def pos = alphabet.indexOf(x)

    if (pos != -1) {
        def alphaSize = alphabet.length()
        int cnt = 0;
        int inverse = 0;

        // find 1 by using modular inverse
        while(true){
            inverse = key1 * cnt % alphaSize;
            if(inverse == 1)
                break;
            cnt++;
        }

        def newPos = (cnt * (pos - key2) % alphaSize)
        return alphabet[newPos]
    }
    return x
}

def encrypt(originalFileName, key1, key2, alphabet) {
    def res = []
    new File(originalFileName).eachLine { myLine ->
        def encLine = ''
        myLine.each { x ->
            encLine += encryptAlpha(alphabet, x, key1, key2)
        }
        res << encLine
    }
    return res
}

def decrypt(encLines, key1, key2, alphabet) {
    def res = []
    encLines.each { myLine ->
        def decLine = ''
        myLine.each { x ->
            decLine += decryptAlpha(alphabet, x, key1, key2)
        }
        res << decLine
    }
    return res
}


def alphabet = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя0123456789.,-;:'


def fileName = System.console().readLine("Read from file: ")
println "Alphabet size: ${alphabet.length()}"
def n = Integer.parseInt(System.console().readLine("First key (n): "))
def k = Integer.parseInt(System.console().readLine("Second key (k): "))

if (gcd(alphabet.length(), n) != 1) {
    println("Key1 (n) and alphabet size (m) are not relatively prime, affine cipher won't work correctly")
    return
}

println "--------- ORIGINAL ---------"
new File(fileName).eachLine { println it }


println "--------- ENCRYPTED ---------"
def encLines = encrypt(fileName, n, k, alphabet)
encLines.each {
    println it
}

println "--------- DECRYPTED ---------"
decrypt(encLines, n, k, alphabet).each {
    println it
}

