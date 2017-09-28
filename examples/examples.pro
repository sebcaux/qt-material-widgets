QT += core gui widgets
TEMPLATE = app
SOURCES = mainwindow.cpp main.cpp
HEADERS = mainwindow.h 
LIBS += ../components/libcomponents.a
INCLUDEPATH += ../components/
TARGET = ../examples-exe

