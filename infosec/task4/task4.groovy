import java.nio.file.Files
import java.nio.file.Paths

def container = "container"
def resultFile = "result"

//def openText = "sometext"
//def extractedFile = "extract"


//def openText = "somedata.png"
def openText = "pic1.png"
def extractedFile = "extract.png"


def hide(String container, String openText, String resultFile) {
    println "Reading file to hide"
    def bits = []
    new File(openText).getBytes().collect {it & 0xFF}.each { aByte ->
        String.format("%8s", Integer.toBinaryString(aByte)).replace(' ', '0').each {bit -> bits << bit}

    }
    int bitIdx = 0
    println "Building new container with the file data"
    new File(container).eachLine {
        if (bitIdx < bits.size()) {
            new File(resultFile) << "${it.trim()}${(bits[bitIdx] == "1") ? " " : ""}\n"
            bitIdx++;
        }
    }
    println "Done"
}

def extract(resultFile, extractedFile) {
    println "Reading container"
    def bits = []
    new File(resultFile).eachLine { line ->
        if (line.length() > 0 && line[-1] == ' ') {
            bits << 1
        } else {
            bits << 0
        }
    }

    println "Converting bits into bytes"
    def bytes = []
    while(bits.size() != 0) {
          def decByteRepr = 0
          def newByte = bits.take(8)
          newByte.eachWithIndex { bit, idx ->
              if (bit == 1) {
                  decByteRepr |= (1 << (7 - idx))
              }
          }
          bytes << decByteRepr
          bits = bits.drop(8)
    }

    println "Writing out extracted file"
    byte[] finalResult = new byte[bytes.size()];
    for (int i = 0; i < finalResult.length; i++) {
        finalResult[i] = bytes.get(i);
    }

    Files.write(Paths.get(extractedFile), finalResult);
    println "Done"
}



hide(container, openText, resultFile)
extract(resultFile, extractedFile)
