QT += core
QT -= gui

CONFIG += c++11

TARGET = NEncryptionKit_Example
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

win32{
    DESTDIR = $$PWD/../bin
    MOC_DIR = $$PWD/build_/moc
    RCC_DIR = $$PWD/build_/rcc
    OBJECTS_DIR = $$PWD/build_/obj
}

# import dll file
include($$PWD/../NEncryptionKit/NEncryptionKit_inc.pri)
