#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T10:57:22
#
#-------------------------------------------------

QT     += core gui widgets
CONFIG += console c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RSRPCalculator
TEMPLATE = app
#QMAKE_CXXFLAGS_RELEASE += -O3
#DEFINES += GTEST_LINKED_AS_SHARED_LIBRARY=1

#LIBS += -lgtest -L/usr/lib/


SOURCES += main.cpp\
        mainwindow.cpp \
    Pathloss/Parameter.cpp \
    Pathloss/PathlossModel.cpp \
    Pathloss/OkumuraHataPathlossModel.cpp \
    Pathloss/PathlossCalculation.cpp \
    Core/BaseStation.cpp \
    Core/Antenna.cpp \
    Core/Sector.cpp \
    RSRP/RsrpCalculation.cpp \
    RSRP/RsrpInitialization.cpp \
    RuskiTest/rsrptestcase.cpp \
    AntennaLoss/AntennaLossFileParser.cpp \
    RuskiTest/AntennaLossFileParserTest.cpp \
    AntennaLoss/AntennaLossFileProvider.cpp \
    MapProvider/MapDataProvider.cpp \
    MapProvider/MapParser.cpp \
    MapProvider/Pixel.cpp \
    AntennaLoss/AntennaLossVerticalCalculator.cpp \
    AntennaLoss/AntennaLossHorizontalCalculator.cpp \
    AntennaLoss/AnetnnaLossCalculator.cpp \
    Core/SectorsControler.cpp \
    Core/AreaCalculation.cpp \
    Core/PixelXY.cpp \
    Core/Receiver.cpp \
    Image.cpp \
    JobQueue.cpp \
    ThreadPool.cpp \
    PixelWorker.cpp \
    AntennaLoss/AntennaLossCalculation.cpp \
    Worker.cpp \
    BaseStationForm.cpp \
    SectorForm.cpp \
    SelectBaseStationForm.cpp \
    ImagePainter.cpp \
    Pathloss/Cost231HataModel.cpp \
    ScribbleArea.cpp \
    ReceiverForm.cpp \
    Rectangle.cpp \
    Canvas.cpp \
    DrawRectangle.cpp \
    MapProvider/wgs84_do_puwg92.cc \
    MapProvider/GeographicalCoordinatesConverter.cpp \
    TerrainProfile.cpp \
    TerrainCanvas.cpp \
    Display/NetworkObjectWizualizator.cpp \
    DataProvider.cpp

HEADERS  += mainwindow.h \
    Pathloss/Pathloss.h \
    Pathloss/IPathlossCalculation.h \
    Pathloss/Parameter.h \
    Pathloss/PathlossModel.h \
    Pathloss/OkumuraHataPathlossModel.h \
    Pathloss/PathlossCalculation.h \
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
    MapProvider/Enviroment.h \
    MapProvider/IMapDataProvider.h \
    MapProvider/MapDataProvider.h \
    MapProvider/MapParser.h \
    MapProvider/Pixel.h \
    AntennaLoss/AntennaLossVerticalCalculator.h \
    AntennaLoss/AntennaLossHorizontalCalculator.h \
    AntennaLoss/AnetnnaLossCalculator.h \
    Core/SectorsControler.h \
    Core/AreaCalculation.h \
    Core/PixelXY.h \
    Core/Receiver.h \
    Image.h \
    JobQueue.h \
    ThreadPool.h \
    PixelWorker.h \
    AntennaLoss/AntennaLossCalculation.h \
    Worker.h \
    BaseStationForm.h \
    SectorForm.h \
    DataProvider.h \
    SelectBaseStationForm.h \
    customstyle.h \
    ImagePainter.h \
    Pathloss/Cost231HataModel.h \
    ScribbleArea.h \
    ReceiverForm.h \
    Rectangle.h \
    Canvas.h \
    DrawRectangle.h \
    MapProvider/wgs84_do_puwg92.h \
    MapProvider/GeographicalCoordinatesConverter.h \
    TerrainProfile.h \
    TerrainCanvas.h \
    Display/NetworkObjectWizualizator.h

FORMS    += mainwindow.ui \
    BaseStationForm.ui \
    SectorForm.ui \
    SelectBaseStationForm.ui \
    ReceiverForm.ui \
    TerrainProfile.ui \
    Display/NetworkObjectWizualizatorForm.ui

DISTFILES +=

RESOURCES += \
    zasoby.qrc
