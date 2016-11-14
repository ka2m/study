def container = "somefile"
def openText = "openfile"
def resultFile = "result"

def hide(String container, String openText, String resultFile) {
    def bits = []
    new File(openText).text.getBytes('UTF-8').each { aByte ->
        String.format("%8s", Integer.toBinaryString(aByte & 0xFF)).replace(' ', '0').each {bit -> bits << bit}
    }
    def lines = []
    new File(container).text.eachLine {
        lines << it.trim()
    }

    if (bits.size() > lines.size()) {
        println "Container is too small for opentext"
        return
    }

    def resText = []
    bits.eachWithIndex { def aBit, int bitIdx ->
        if (aBit == "1") {
            resText << lines[bitIdx] + " " + "\n"
        } else {
            resText << lines[bitIdx] + "\n"
        }
    }

    lines.drop(bits.size()).each { resText << it + "\n" }

    resText.each {
        new File(resultFile) << it
    }
}

def extract(resultFile) {
    def bits = []
    new File(resultFile).eachLine { line ->
        if (line.length() > 0 && line[-1] == ' ') {
            bits << 1
        } else {
            bits << 0
        }
    }

    def hiddenStr = ""
    while(bits.size() != 0) {

        def data = Integer.parseInt(bits.take(8).join(''), 2)
        hiddenStr += Character.toString ((char) data.byteValue());
        bits = bits.drop(8)
    }

    println hiddenStr
}


//hide(container, openText, resultFile)
extract(resultFile)