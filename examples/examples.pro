QT += core gui widgets
TEMPLATE = app
SOURCES = mainwindow.cpp \
    main.cpp \
    avatarsettingseditor.cpp \
    badgesettingseditor.cpp \
    checkboxsettingseditor.cpp \
    circularprogresssettingseditor.cpp
HEADERS = mainwindow.h \
    avatarsettingseditor.h \
    badgesettingseditor.h \
    checkboxsettingseditor.h \
    circularprogresssettingseditor.h
LIBS += ../components/libcomponents.a
INCLUDEPATH += ../components/
TARGET = ../examples-exe

RESOURCES += \
    examples.qrc

FORMS += \
    avatarsettingsform.ui \
    badgesettingsform.ui \
    checkboxsettingsform.ui \
    circularprogresssettingsform.ui
