QT       += core gui qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-material-widgets
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    style.cpp \
    components/appbar.cpp \
    components/checkbox.cpp \
    components/dialog.cpp \
    components/flatbutton.cpp \
    components/iconbutton.cpp \
    components/iconmenu.cpp \
    components/list.cpp \
    components/radiobutton.cpp \
    components/slider.cpp \
    components/tab.cpp \
    components/tabs.cpp \
    components/textfield.cpp \
    components/table.cpp \
    lib/ripple.cpp \
    lib/rippleoverlay.cpp \
    examples/frame.cpp \
    examples/examplelist.cpp \
    examples/flatbuttonexamples.cpp \
    examples/exampleview.cpp \
    examples/about.cpp \
    examples/appbarexamples.cpp \
    examples/iconbuttonexamples.cpp \
    examples/tabsexamples.cpp \
    examples/tableexamples.cpp

HEADERS  += mainwindow.h \
    style.h \
    components/appbar.h \
    components/checkbox.h \
    components/dialog.h \
    components/flatbutton.h \
    components/iconbutton.h \
    components/iconmenu.h \
    components/list.h \
    components/radiobutton.h \
    components/slider.h \
    components/tab.h \
    components/tabs.h \
    components/textfield.h \
    components/table.h \
    lib/ripple.h \
    lib/rippleoverlay.h \
    examples/frame.h \
    examples/examplelist.h \
    examples/flatbuttonexamples.h \
    examples/exampleview.h \
    examples/about.h \
    examples/appbarexamples.h \
    examples/iconbuttonexamples.h \
    components/tabsexamples.h \
    examples/tabsexamples.h \
    examples/tableexamples.h
