QT += core gui widgets
TEMPLATE = app
CONFIG += c++11
TARGET = examples
DESTDIR = "$$PWD/../bin"

greaterThan(QT_MAJOR_VERSION, 5) {
    QT += statemachine
}

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
    $$PWD/progresssettingseditor.cpp \
    $$PWD/radiobuttonsettingseditor.cpp \
    $$PWD/scrollbarsettingseditor.cpp \
    $$PWD/settingseditor.cpp \
    $$PWD/slidersettingseditor.cpp \
    $$PWD/snackbarsettingseditor.cpp \
    $$PWD/tabssettingseditor.cpp \
    $$PWD/textfieldsettingseditor.cpp \
    $$PWD/switchsettingseditor.cpp

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
    $$PWD/progresssettingseditor.h \
    $$PWD/radiobuttonsettingseditor.h \
    $$PWD/scrollbarsettingseditor.h \
    $$PWD/settingseditor.h \
    $$PWD/slidersettingseditor.h \
    $$PWD/snackbarsettingseditor.h \
    $$PWD/tabssettingseditor.h \
    $$PWD/textfieldsettingseditor.h \
    $$PWD/switchsettingseditor.h

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
    $$PWD/switchsettingsform.ui

RESOURCES += \
    $$PWD/examples.qrc

INCLUDEPATH += $$PWD/../components
LIBS += -L"$$PWD/../bin"
android:LIBS += -lqtmaterialwidgets_$${QT_ARCH}
else:LIBS += -lqtmaterialwidgets
