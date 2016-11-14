import static groovy.io.FileType.FILES
import groovy.json.JsonSlurper

def getFileSignature(String pathToFile, int sigBegin, int sigSize) {
    return new String ((new File(pathToFile).text.getBytes() as List).drop(sigBegin).take(sigSize) as byte[])
}

def config = new JsonSlurper().parseText(new File('config.json').text)
def origSignature = getFileSignature(config.origFile, config.begin, config.size)
new File(config.dir).traverse(type: FILES) {
    def signature = getFileSignature(it.path, config.begin, config.size)
    if (signature == origSignature) {
        println it.path
    }
}
