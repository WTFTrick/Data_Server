greaterThan(QT_MAJOR_VERSION, 4): QT += network

QT += core
QT -= gui
TARGET = Data_Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    dserver.cpp \
    dgenerator.cpp \
    tcpserver.cpp

HEADERS += \
    server.h \
    dserver.h \
    dgenerator.h \
    ichannel.h \
    tcpserver.h

