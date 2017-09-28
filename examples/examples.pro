QT += core gui widgets
TEMPLATE = app
SOURCES = \
    mainwindow.cpp \
    main.cpp \
    avatarsettingseditor.cpp
HEADERS = \
    mainwindow.h \
    avatarsettingseditor.h
LIBS += ../components/libcomponents.a
INCLUDEPATH += ../components/
TARGET = ../examples-exe
RESOURCES += resources.qrc
FORMS += \
    avatarsettingsform.ui
