QT       += core gui qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-material-widgets
TEMPLATE = app

#DEFINES += DEBUG_LAYOUT=1

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
    examples/iconmenuexamples.cpp \
    lib/scaleeffect.cpp \
    lib/style.cpp \
    components/searchfield.cpp \
    lib/theme.cpp \
    components/slider_internal.cpp \
    components/flatbutton_internal.cpp \
    components/toggle_internal.cpp \
    components/tabs_internal.cpp \
    components/fab.cpp \
    components/badge.cpp \
    components/progress.cpp \
    components/selectfield.cpp \
    lib/checkable.cpp \
    lib/checkable_internal.cpp \
    components/snackbar.cpp \
    components/textfield_internal.cpp \
    components/drawer.cpp \
    components/snackbar_internal.cpp \
    components/circularprogress.cpp \
    components/circularprogress_internal.cpp \
    components/progress_internal.cpp \
    components/scrollwidget.cpp \
    components/scrollwidget_internal.cpp

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
    examples/iconmenuexamples.h \
    lib/scaleeffect.h \
    lib/style.h \
    components/searchfield.h \
    lib/theme.h \
    lib/theme_p.h \
    components/flatbutton_p.h \
    components/slider_internal.h \
    components/flatbutton_internal.h \
    components/raisedbutton_p.h \
    components/toggle_p.h \
    components/toggle_internal.h \
    components/iconbutton_p.h \
    components/tabs_p.h \
    components/tabs_internal.h \
    components/fab.h \
    components/badge.h \
    components/progress.h \
    components/selectfield.h \
    components/fab_p.h \
    components/radiobutton_p.h \
    components/checkbox_p.h \
    lib/checkable.h \
    lib/checkable_p.h \
    lib/checkable_internal.h \
    components/snackbar.h \
    components/snackbar_p.h \
    components/textfield_p.h \
    components/textfield_internal.h \
    components/badge_p.h \
    components/drawer.h \
    components/avatar_p.h \
    components/snackbar_internal.h \
    components/progress_p.h \
    components/circularprogress.h \
    components/circularprogress_p.h \
    components/circularprogress_internal.h \
    components/progress_internal.h \
    components/scrollwidget_p.h \
    components/scrollwidget.h \
    components/scrollwidget_internal.h

RESOURCES += \
    resources.qrc
