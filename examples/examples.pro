QT += core gui widgets
TEMPLATE = app
CONFIG += c++11

SOURCES = \
    $$PWD/appbarsettingseditor.cpp \
    $$PWD/autocompletesettingseditor.cpp \
    $$PWD/avatarsettingseditor.cpp \
    $$PWD/badgesettingseditor.cpp \
    $$PWD/checkboxsettingseditor.cpp \
    $$PWD/circularprogresssettingseditor.cpp \
    $$PWD/dialogsettingseditor.cpp \
    $$PWD/drawersettingseditor.cpp \
    $$PWD/fabsettingseditor.cpp \
    $$PWD/flatbuttonsettingseditor.cpp \
    $$PWD/iconbuttonsettingseditor.cpp \
    $$PWD/main.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/menusettingseditor.cpp \
    $$PWD/progresssettingseditor.cpp \
    $$PWD/radiobuttonsettingseditor.cpp \
    $$PWD/raisedbuttonsettingseditor.cpp \
    $$PWD/scrollbarsettingseditor.cpp \
    $$PWD/settingseditor.cpp \
    $$PWD/slidersettingseditor.cpp \
    $$PWD/snackbarsettingseditor.cpp \
    $$PWD/tabssettingseditor.cpp \
    $$PWD/textfieldsettingseditor.cpp \
    $$PWD/togglesettingseditor.cpp

HEADERS = \
    $$PWD/appbarsettingseditor.h \
    $$PWD/autocompletesettingseditor.h \
    $$PWD/avatarsettingseditor.h \
    $$PWD/badgesettingseditor.h \
    $$PWD/checkboxsettingseditor.h \
    $$PWD/circularprogresssettingseditor.h \
    $$PWD/dialogsettingseditor.h \
    $$PWD/drawersettingseditor.h \
    $$PWD/fabsettingseditor.h \
    $$PWD/flatbuttonsettingseditor.h \
    $$PWD/iconbuttonsettingseditor.h \
    $$PWD/mainwindow.h \
    $$PWD/menusettingseditor.h \
    $$PWD/progresssettingseditor.h \
    $$PWD/radiobuttonsettingseditor.h \
    $$PWD/raisedbuttonsettingseditor.h \
    $$PWD/scrollbarsettingseditor.h \
    $$PWD/settingseditor.h \
    $$PWD/slidersettingseditor.h \
    $$PWD/snackbarsettingseditor.h \
    $$PWD/tabssettingseditor.h \
    $$PWD/textfieldsettingseditor.h \
    $$PWD/togglesettingseditor.h

FORMS += \
    $$PWD/appbarsettingsform.ui \
    $$PWD/avatarsettingsform.ui \
    $$PWD/badgesettingsform.ui \
    $$PWD/checkboxsettingsform.ui \
    $$PWD/circularprogresssettingsform.ui \
    $$PWD/dialogsettingsform.ui \
    $$PWD/drawersettingsform.ui \
    $$PWD/fabsettingsform.ui \
    $$PWD/flatbuttonsettingsform.ui \
    $$PWD/iconbuttonsettingsform.ui \
    $$PWD/progresssettingsform.ui \
    $$PWD/radiobuttonsettingsform.ui \
    $$PWD/scrollbarsettingsform.ui \
    $$PWD/slidersettingsform.ui \
    $$PWD/snackbarsettingsform.ui \
    $$PWD/tabssettingsform.ui \
    $$PWD/textfieldsettingsform.ui \
    $$PWD/togglesettingsform.ui

RESOURCES += \
    examples.qrc

LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
TARGET = examples-exe
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
