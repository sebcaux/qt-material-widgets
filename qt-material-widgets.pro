QT       += core gui qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-material-widgets
TEMPLATE = app

DEFINES += DEBUG_LAYOUT=1

SOURCES += main.cpp\
        mainwindow.cpp \
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
    lib/customshadoweffect.cpp \
    examples/frame.cpp \
    examples/examplelist.cpp \
    examples/flatbuttonexamples.cpp \
    examples/exampleview.cpp \
    examples/about.cpp \
    examples/appbarexamples.cpp \
    examples/iconbuttonexamples.cpp \
    examples/tabsexamples.cpp \
    examples/tableexamples.cpp \
    components/raisedbutton.cpp \
    examples/raisedbuttonexamples.cpp \
    examples/sliderexamples.cpp \
    components/toggle.cpp \
    examples/toggleexamples.cpp \
    examples/radiobuttonexamples.cpp \
    examples/checkboxexamples.cpp \
    examples/textfieldexamples.cpp \
    examples/listexamples.cpp \
    components/avatar.cpp \
    examples/avatarexamples.cpp \
    examples/menuexamples.cpp \
    components/menu.cpp \
    components/scrollbar.cpp \
    examples/iconmenuexamples.cpp \
    lib/scaleeffect.cpp \
    lib/style.cpp

HEADERS  += mainwindow.h \
    components/appbar.h \
    components/checkbox.h \
    components/dialog.h \
    components/flatbutton.h \
    components/iconbutton.h \
    components/iconmenu.h \
    components/list.h \
    components/radiobutton.h \
    components/slider.h \
    components/slider_p.h \
    components/tab.h \
    components/tabs.h \
    components/textfield.h \
    components/table.h \
    lib/ripple.h \
    lib/rippleoverlay.h \
    lib/customshadoweffect.h \
    examples/frame.h \
    examples/examplelist.h \
    examples/flatbuttonexamples.h \
    examples/exampleview.h \
    examples/about.h \
    examples/appbarexamples.h \
    examples/iconbuttonexamples.h \
    examples/tabsexamples.h \
    examples/tableexamples.h \
    components/raisedbutton.h \
    examples/raisedbuttonexamples.h \
    examples/sliderexamples.h \
    components/toggle.h \
    examples/toggleexamples.h \
    examples/radiobuttonexamples.h \
    examples/checkboxexamples.h \
    examples/textfieldexamples.h \
    examples/listexamples.h \
    components/avatar.h \
    examples/avatarexamples.h \
    examples/menuexamples.h \
    components/menu.h \
    components/scrollbar.h \
    examples/iconmenuexamples.h \
    lib/scaleeffect.h \
    lib/style.h

RESOURCES += \
    resources.qrc
