#-------------------------------------------------
#
# Project created by QtCreator 2019-09-07T13:39:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DigitRecognition
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += DLIB_USE_CUDA

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 console


INCLUDEPATH+= "../../dlib-19.17/Install/include"

SOURCES += \
        digitpredictor.cpp \
        main.cpp \
        digitrecognitionapp.cpp

HEADERS += \
        ../../dlib-19.17/dlib/cuda/cuda_dlib.h \
        digitpredictor.h \
        digitrecognitionapp.h

FORMS += \
        digitrecognitionapp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



# ===== 64bit dlib =====
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../dlib-19.17/Install/lib/ -ldlib19.17.0_release_64bit_msvc1916
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../dlib-19.17/Install/lib/ -ldlib19.17.0_debug_64bit_msvc1916

INCLUDEPATH += $$PWD/../../dlib-19.17/Install/include
DEPENDPATH += $$PWD/../../dlib-19.17/Install/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../dlib-19.17/Install/lib/libdlib19.17.0_release_64bit_msvc1916.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../dlib-19.17/Install/lib/libdlib19.17.0_debug_64bit_msvc1916.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../dlib-19.17/Install/lib/dlib19.17.0_release_64bit_msvc1916.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../dlib-19.17/Install/lib/dlib19.17.0_debug_64bit_msvc1916.lib

# ===== 64bit cuda =====
win32: LIBS += -L$$PWD/'../../../Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.0/lib/x64/' -lcurand -lcudart -lcuda -lcublas -lcusolver

INCLUDEPATH += $$PWD/'../../../Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.0/lib/x64'
DEPENDPATH += $$PWD/'../../../Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.0/lib/x64'


win32: LIBS += -L$$PWD/../../../Users/jlo/Documents/Software/cudnn-10.0-windows10-x64-v7.5.1.10/cuda/lib/x64/ -lcudnn

INCLUDEPATH += $$PWD/../../../Users/jlo/Documents/Software/cudnn-10.0-windows10-x64-v7.5.1.10/cuda/lib/x64
DEPENDPATH += $$PWD/../../../Users/jlo/Documents/Software/cudnn-10.0-windows10-x64-v7.5.1.10/cuda/lib/x64


