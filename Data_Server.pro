greaterThan(QT_MAJOR_VERSION, 4): QT += network

QT += core
QT -= gui
TARGET = Data_Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp

HEADERS += \
    server.h

