TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    MapDataProvider.cpp \
    Pixel.cpp \
    MapParser.cpp

HEADERS += \
    IMapDataProvider.h \
    MapDataProvider.h \
    Pixel.h \
    MapParser.h \
    Enviroment.h
