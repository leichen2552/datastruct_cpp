TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Exception.cpp \
    Object.cpp \
    DTstring.cpp

HEADERS += \
    Exception.h \
    SmartPointer.h \
    Object.h \
    List.h \
    SeqList.h \
    StaticList.h \
    DynamicList.h \
    Array.h \
    Sort.h \
    DTstring.h \
    StaticArray.h \
    DynamicArray.h
