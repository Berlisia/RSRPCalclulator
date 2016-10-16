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
    Core/Pixel.cpp \
    Core/Sector.cpp \
    RSRP/RsrpCalculation.cpp \
    RSRP/RsrpInitialization.cpp \
    RuskiTest/rsrptestcase.cpp \
    AntennaLoss/AntennaLossFileParser.cpp \
    RuskiTest/AntennaLossFileParserTest.cpp \
    AntennaLoss/AntennaLossFileProvider.cpp \
    utest/antennalossfileprovidertest.cpp

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
    Core/Pixel.h \
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
    utest/antennalossfileparsermock.h

FORMS    += mainwindow.ui \
    dialog.ui

DISTFILES +=
