#-------------------------------------------------
#
# Project created by QtCreator 2016-08-03T11:12:42
#
#-------------------------------------------------

# 引入源码
SOURCES += $$PWD/src/nencryptionkit.cpp

HEADERS += $$PWD/inc/nencryptionkit.h \
        $$PWD/inc/nencryptionkit_global.h
INCLUDEPATH += $$PWD/inc/

# 引入第三方源码
include($$PWD/3rdparty/botan/botan.pri)
INCLUDEPATH += $$PWD/3rdparty/botan/
