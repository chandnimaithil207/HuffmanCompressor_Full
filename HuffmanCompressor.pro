QT += core gui widgets

CONFIG += c++17

TARGET = HuffmanCompressor
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    huffman.cpp

HEADERS += \
    mainwindow.h \
    huffman.h

FORMS += \
    mainwindow.ui
