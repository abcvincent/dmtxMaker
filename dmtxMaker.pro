#-------------------------------------------------
#
# Project created by QtCreator 2020-01-31T09:36:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dmtxMaker
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp\
        libdmtx0.7.5/dmtx.c \
        libdmtx0.7.5/dmtxbytelist.c \
        libdmtx0.7.5/dmtxdecode.c \
        libdmtx0.7.5/dmtxdecodescheme.c \
        libdmtx0.7.5/dmtxencode.c \
        libdmtx0.7.5/dmtxencodeascii.c \
        libdmtx0.7.5/dmtxencodebase256.c \
        libdmtx0.7.5/dmtxencodec40textx12.c \
        libdmtx0.7.5/dmtxencodeedifact.c \
        libdmtx0.7.5/dmtxencodeoptimize.c \
        libdmtx0.7.5/dmtxencodescheme.c \
        libdmtx0.7.5/dmtxencodestream.c \
        libdmtx0.7.5/dmtximage.c \
        libdmtx0.7.5/dmtxmatrix3.c \
        libdmtx0.7.5/dmtxmessage.c \
        libdmtx0.7.5/dmtxplacemod.c \
        libdmtx0.7.5/dmtxreedsol.c \
        libdmtx0.7.5/dmtxregion.c \
        libdmtx0.7.5/dmtxscangrid.c \
        libdmtx0.7.5/dmtxsymbol.c \
        libdmtx0.7.5/dmtxtime.c \
        libdmtx0.7.5/dmtxvector2.c

HEADERS += \
        widget.h\
        libdmtx0.7.5/dmtx.h \
        libdmtx0.7.5/dmtxstatic.h

INCLUDEPATH += libdmtx0.7.5

FORMS += \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#unix|win32: LIBS += -L$$PWD/./ -llibdmtx
#INCLUDEPATH += $$PWD/.
#DEPENDPATH += $$PWD/.
