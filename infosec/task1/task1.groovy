def crc32(byte[] bytes) {
    return new java.util.zip.CRC32().with { update bytes; value }
}

def myCrc32(byte[] bytes) {
    def remainder = 0xFFFFFFFF
    def multiple = 0
    def poly = 0xEDB88320

    bytes.each { b ->
        remainder ^= b
        for (int i = 0; i < 8; i++) {
             multiple = (remainder & 1) ? poly : 0;
            remainder = (remainder >> 1) ^ multiple;
        }
    }
    return remainder ^ 0xFFFFFFFF
}


def origFile = 'file'
def fileBytes = new File(origFile).text.getBytes()
def origRes = crc32(fileBytes)
def myRes = myCrc32(fileBytes)


println "java.util.ZIP CRC32: ${Long.toString(origRes, 16)}"
println "My Ross-based CRC32: ${Long.toString(myRes, 16)}"
