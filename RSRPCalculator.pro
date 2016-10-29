#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T10:57:22
#
#-------------------------------------------------

QT       += core gui
CONFIG += console c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RSRPCalculator
TEMPLATE = app
DEFINES += GTEST_LINKED_AS_SHARED_LIBRARY=1

LIBS += -lgtest -L/usr/lib/


SOURCES += main.cpp\
        mainwindow.cpp \
    Pathloss/Parameter.cpp \
    Pathloss/PathlossModel.cpp \
    Pathloss/OkumuraHataPathlossModel.cpp \
    Pathloss/PathlossCalculation.cpp \
    Pathloss/OkumuraParameterForSector.cpp \
    Core/BaseStation.cpp \
    Core/Antenna.cpp \
    Core/Sector.cpp \
    RSRP/RsrpCalculation.cpp \
    RSRP/RsrpInitialization.cpp \
    RuskiTest/rsrptestcase.cpp \
    AntennaLoss/AntennaLossFileParser.cpp \
    RuskiTest/AntennaLossFileParserTest.cpp \
    AntennaLoss/AntennaLossFileProvider.cpp \
    utest/antennalossfileprovidertest.cpp \
    MapProvider/MapDataProvider.cpp \
    MapProvider/MapParser.cpp \
    MapProvider/Pixel.cpp \
    utest/mapdataprovidertest.cpp \
    AntennaLoss/AntennaLossVerticalCalculator.cpp \
    utest/antennalossverticalclaculatortest.cpp \
    AntennaLoss/AntennaLossHorizontalCalculator.cpp \
    AntennaLoss/AnetnnaLossCalculator.cpp \
    utest/antennalosshorizontalcalculatortest.cpp \
    AntennaLoss/AnetnnaLossProvider.cpp \
    utest/pixelfindertest.cpp \
    Core/SectorsControler.cpp \
    Core/AreaCalculation.cpp \
    Core/HorizontalCalculation.cpp \
    Core/PixelControler.cpp \
    Core/PixelXY.cpp \
    Core/Receiver.cpp \
    utest/calculatersrpwithoughtpathloss.cpp

HEADERS  += mainwindow.h \
    Pathloss/Pathloss.h \
    Pathloss/IPathlossCalculation.h \
    Pathloss/Parameter.h \
    Pathloss/PathlossModel.h \
    Pathloss/OkumuraHataPathlossModel.h \
    myunorderedmap.h \
    Pathloss/PathlossCalculation.h \
    Pathloss/OkumuraHataPathlossMap.h \
    Pathloss/OkumuraParameterForSector.h \
    Core/Sector.h \
    Core/BaseStation.h \
    Core/Antenna.h \
    RSRP/IRsrpCalculation.h \
    RSRP/RsrpCalculation.h \
    RSRP/RsrpInitialization.h \
    RuskiTest/rsrptestcase.h \
    AntennaLoss/AntennaLossFileParser.h \
    RuskiTest/AntennaLossFileParserTest.h \
    AntennaLoss/AntennaLossFileProvider.h \
    AntennaLoss/IAntennaLossFileProvider.h \
    utest/antennalossfileparsermock.h \
    MapProvider/Enviroment.h \
    MapProvider/IMapDataProvider.h \
    MapProvider/MapDataProvider.h \
    MapProvider/MapParser.h \
    MapProvider/Pixel.h \
    Pathloss/okumurahatapathlossmap.h \
    AntennaLoss/AntennaLossVerticalCalculator.h \
    utest/imapdataprovidermock.h \
    utest/antennalossfileprovidermock.h \
    AntennaLoss/AntennaLossHorizontalCalculator.h \
    AntennaLoss/AnetnnaLossCalculator.h \
    AntennaLoss/AnetnnaLossProvider.h \
    Core/SectorsControler.h \
    Core/AreaCalculation.h \
    Core/HorizontalCalculation.h \
    Core/PixelControler.h \
    Core/PixelXY.h \
    Core/Receiver.h

FORMS    += mainwindow.ui \
    dialog.ui

DISTFILES +=
