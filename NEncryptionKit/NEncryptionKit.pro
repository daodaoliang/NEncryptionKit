#-------------------------------------------------
#
# Project created by QtCreator 2016-08-03T11:12:42
#
#-------------------------------------------------

QT       -= gui

TARGET = NEncryptionKit
TEMPLATE = lib

DEFINES += NENCRYPTIONKIT_LIBRARY

# 导入源码
include($$PWD/NEncryptionKit_src.pri)

# 设置版本信息
RC_FILE += ./NEncryptionKit_resource.rc

# 设定编译输出路径
win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = ./build_/dist
        } else {
            target_path = ./build_/debug
        }
        DESTDIR = ./../bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        OBJECTS_DIR = $$target_path/obj
}

# 输出编译套件信息
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(the NEncryptionKit will create in folder: $$target_path)
