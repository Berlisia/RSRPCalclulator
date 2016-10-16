import struct
from multiprocessing.pool import ThreadPool
import multiprocessing
import copy_reg
import types
from timeit import default_timer as timer

def _reduce_method(m):
    if m.im_self is None:
        return getattr, (m.im_class, m.im_func.func_name)
    else:
        return getattr, (m.im_self, m.im_func.func_name)

copy_reg.pickle(types.MethodType, _reduce_method)


class mapPart:
    def __init__(self, _width, _height, _begin, _end, _unpackedData):
        self.width = _width
        self.height = _height
        self.begin = _begin
        self.end = _end
        self.unpackedData = _unpackedData
        self.heights = [[int for x in range(self.width)] for x in range(self.end - self.begin)]

    def coutElevation(self):
        for r in range(self.begin, self.end):
            i = r-self.begin
            for c in range(0, self.width):
                self.heights[i][c] = self.unpackedData[(self.width * r) + c]


class fileParser:
    def __init__(self, _fileName):
        self.fileName = _fileName
        self.ncols = 0
        self.nrows = 0
        self.magicNumber = 0
        self.unpackedData = str()
        self.nubmerOfThreads = 8
        self.listOfMapParts = []
        self.parse()

    def parseHeader(self):
        try:
            hdrFile = open(self.fileName + ".hdr", "r")
        except:
            print ("No such file: " + self.fileName + ".hdr")
            exit()
        hdrFileStr = hdrFile.read()
        hdrFile.close()
        fileLines = hdrFileStr.strip().splitlines()
        tempHeader = {}
        for line in fileLines:
            key, _, value = line.partition(" ")
            tempHeader[key] = value
        self.nrows = int(tempHeader['nrows'])
        self.ncols = int(tempHeader['ncols'])

    def parseBil(self):
        try:
            linFile = open(self.fileName + ".bil", "rb")
        except:
            print ("No such file: " + self.fileName + ".lin")
            exit()
        linFileStr = linFile.read()
        linFile.close()
        key = "<%dH" % (int(self.nrows * self.ncols),)
        self.unpackedData = struct.unpack(key, linFileStr)

    def cutMap(self):
        #self.nubmerOfThreads = 35
        numbersOfRowsForThread = self.nrows/self.nubmerOfThreads
        numbersOfRowsForLastThread = 0

        if self.nubmerOfThreads > 1:
            numbersOfRowsForLastThread = self.nrows - numbersOfRowsForThread*(self.nubmerOfThreads-1)

        if self.nubmerOfThreads == 1:
            self.listOfMapParts.append(mapPart(self.nrows, self.ncols, 0, self.ncols, self.unpackedData))
            return
        for numberOfThread in range(self.nubmerOfThreads-1):
            begin = numberOfThread * numbersOfRowsForThread
            end = numberOfThread * numbersOfRowsForThread + numbersOfRowsForThread
            self.listOfMapParts.append(mapPart(self.nrows, self.ncols, begin, end,
                                               self.unpackedData))
        begin = self.nrows - numbersOfRowsForLastThread
        end = self.nrows
        self.listOfMapParts.append(mapPart(self.nrows, self.ncols, begin, end,
                                           self.unpackedData))

        #self.nubmerOfThreads = 2

    def startParsing(self, mapPart):
        mapPart.coutElevation()

    def parse(self):
        self.parseHeader()
        self.parseBil()
        self.cutMap()
        print ("Parsing map with " + str(self.nubmerOfThreads) + " thread/s")
        print (len(self.listOfMapParts))
        procespool = ThreadPool(processes=self.nubmerOfThreads)
        procespool.map(self.startParsing, self.listOfMapParts)

s = timer()
fileParser("dtm")
e = timer()
print e - s