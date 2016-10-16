from timeit import default_timer as timer
import struct
import sys
import os
import getopt

def openFileAndReturnContent(fileName, flags):
    try:
        file = open(fileName, flags)
    except:
        print ("File not exist "+ fileName)
        exit()
    fileContent = file.read()
    file.close()
    return fileContent



class fileParser:
    def __init__(self, _fileName, _outputFileName, _levelsOfGray):
        self.fileName = _fileName
        self.outputFileName = _outputFileName
        self.levelsOfGray = _levelsOfGray
        self.numberOfRows = 0
        self.numberOfCols = 0
        self.unpackData = str()
        self.praseHeader()
        self.parseBil()
        self.saveToPgm()
    def praseHeader(self):
        headerContent = openFileAndReturnContent(self.fileName + ".hdr", "r")
        self.numberOfCols = int(headerContent.splitlines()[4].partition(" ")[2])
        self.numberOfRows = int(headerContent.splitlines()[5].partition(" ")[2])

    def parseBil(self):
        bilContent = openFileAndReturnContent(self.fileName + ".bil", "rb")

        unpackKey = '<%dH' % int(self.numberOfRows*self.numberOfCols)
        self.unpackData = struct.unpack(unpackKey, bilContent)

    def writeHeaderPgm(self, pgmFile):
        pgmFile.write("P2\n# " + self.outputFileName + "\n" + str(self.numberOfCols)
                      + " " + str(self.numberOfRows) + "\n" + str(self.levelsOfGray) + "\n")
        self.saveData(pgmFile)

    def saveData(self, pmgImage):
        for colNumber in range(self.numberOfCols):
            a = self.numberOfRows * colNumber
            for rowNumber in range(self.numberOfRows):
                pmgImage.write(str(self.unpackData[a + rowNumber]) + " ")
            pmgImage.write("\n")

    def saveToPgm(self):
        pmgImage = open(self.outputFileName + ".pgm", 'w+')
        self.writeHeaderPgm(pmgImage)

def main(argv, scriptName):
    try:
        opts, args = getopt.getopt(argv, "hi:o:g:", ["iFileName=", "oFileName=", "levelsOfGray="])
    except getopt.GetoptError:
        print scriptName + ' -i <inputFile> -o <outputFile> -g <levelsOfGray>'
        exit()
    inPutFileName = 0
    outPutFileName = 0
    levelsOfGray = 0
    for opt, arg in opts:
        if opt == '-h':
            print scriptName + ' -i <inputFile> -o <outputFile> -g <levelsOfGray>'
            exit()
        elif opt in ("-i", "--iFileName"):
            inPutFileName = arg
        elif opt in ("-o", "--oFileName"):
            outPutFileName = arg
        elif opt in ("-g", "--levelsOfGray"):
            levelsOfGray = arg
    if not(inPutFileName and inPutFileName and levelsOfGray):
        print scriptName + ' -i <inputFile> -o <outputFile> -g <levelsOfGray>'
        exit()
    begin = timer()
    fileParser(inPutFileName, outPutFileName, levelsOfGray)
    end = timer()
    print ("Generated in " + str(end - begin) + " secounds")

if __name__ == "__main__":
    main(sys.argv[1:], os.path.basename(__file__))
