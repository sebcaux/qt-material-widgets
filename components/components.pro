TEMPLATE = lib
CONFIG += staticlib
SOURCES = \
    qtmaterialavatar.cpp \
    lib/qtmaterialstyle.cpp \
    lib/qtmaterialtheme.cpp \
    qtmaterialbadge.cpp \
    lib/qtmaterialoverlaywidget.cpp \
    qtmaterialcheckbox.cpp \
    lib/qtmaterialcheckable_internal.cpp \
    lib/qtmaterialcheckable.cpp \
    lib/qtmaterialripple.cpp \
    lib/qtmaterialrippleoverlay.cpp \
    qtmaterialcircularprogress_internal.cpp \
    qtmaterialcircularprogress.cpp
HEADERS = \
    qtmaterialavatar_p.h \
    qtmaterialavatar.h \
    lib/qtmaterialstyle_p.h \
    lib/qtmaterialstyle.h \
    lib/qtmaterialtheme_p.h \
    lib/qtmaterialtheme.h \
    qtmaterialbadge_p.h \
    qtmaterialbadge.h \
    lib/qtmaterialoverlaywidget.h \
    qtmaterialcheckbox_p.h \
    qtmaterialcheckbox.h \
    lib/qtmaterialcheckable_internal.h \
    lib/qtmaterialcheckable_p.h \
    lib/qtmaterialripple.h \
    lib/qtmaterialrippleoverlay.h \
    lib/qtmaterialcheckable.h \
    qtmaterialcircularprogress_internal.h \
    qtmaterialcircularprogress_p.h \
    qtmaterialcircularprogress.h
RESOURCES += \
    resources.qrc
