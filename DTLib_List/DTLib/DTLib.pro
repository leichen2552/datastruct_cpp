TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Exception.cpp \
    Object.cpp

HEADERS += \
    Exception.h \
    SmartPointer.h \
    Object.h \
    List.h
