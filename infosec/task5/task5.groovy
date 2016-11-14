def encrypt(alpha, x, key1, key2) {
    def lowercase = (x.toUpperCase() != x)
    def pos = (lowercase) ? alpha.indexOf(x.toUpperCase()) : alpha.indexOf(x)
    if (pos != -1) {
        def alphaSize = alpha.length()
        def newPos = (pos * key1 + key2) % alphaSize
        if (newPos >= alphaSize) {
            newPos -= alphaSize
        }
        return [true, ((lowercase) ? alpha[newPos].toLowerCase(): alpha[newPos])]
    }
    return [false, null]
}

def decrypt(alpha, x, key1, key2) {
    def lowercase = (x.toUpperCase() != x)
    def pos = (lowercase) ? alpha.indexOf(x.toUpperCase()) : alpha.indexOf(x)
    if (pos != -1) {
        def alphaSize = alpha.length()
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
        if (newPos < 0) {
            newPos = alphaSize + newPos
        }
        if (newPos >= alphaSize) {
            newPos -= alphaSize
        }

        return [true, ((lowercase) ? alpha[newPos].toLowerCase(): alpha[newPos])]
    }
    return [false, null]
}


def eng = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
def rus = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ'
def num = '0123456789'
def special = '.,-;:'


def n = 17
def k = 20


def encLines = []
println "--------- ORIGINAL ---------"
new File('orig').eachLine { println it}


println "--------- ENCRYPTED ---------"
new File('orig').eachLine { myLine ->
    def encLine = ''
    myLine.each { x ->
        itm = x
        def vars = [encrypt(eng, x, n, k),
                    encrypt(rus, x, n, k),
                    encrypt(special, x, n, k),
                    encrypt(num, x, n, k)].findAll { takeThis, _ -> takeThis == true }.collect { _, val -> val }
        if (vars.size() != 0) {
            itm = vars[0]
        }

        encLine += itm
    }
    encLines << encLine
    println encLine
}
println "--------- DECRYPTED ---------"
encLines.each { myLine ->
    def decLine = ''
    myLine.each { x ->
        itm = x
        def vars = [decrypt(eng, x, n, k),
                    decrypt(rus, x, n, k),
                    decrypt(special, x, n, k),
                    decrypt(num, x, n, k)].findAll { takeThis, _ -> takeThis == true }.collect { _, val -> val }
        if (vars.size() != 0) {
            itm = vars[0]
        }

        decLine += itm
    }
//    encLines << encLine
    println decLine
}