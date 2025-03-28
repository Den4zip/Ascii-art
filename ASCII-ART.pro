QT += core gui widgets
CONFIG += c++17
TARGET = AsciiArtQt
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           imageconverter.cpp

HEADERS += mainwindow.h \
           imageconverter.h

FORMS += mainwindow.ui

# OpenCV
unix {
    CONFIG += link_pkgconfig
    INCLUDEPATH += /usr/include/opencv4
    LIBS += -L/usr/lib \
            -lopencv_core \
            -lopencv_imgproc \
            -lopencv_highgui \
            -lopencv_imgcodecs
}
