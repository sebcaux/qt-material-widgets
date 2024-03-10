set(LIB_TARGET_NAME ${PROJECT_NAME})


set(SOURCES 
    layouts/qtmaterialslidelayout.cpp 
    lib/qtmaterialcheckable.cpp 
    lib/qtmaterialcheckable_internal.cpp 
    lib/qtmaterialoverlaywidget.cpp 
    lib/qtmaterialripple.cpp 
    lib/qtmaterialrippleoverlay.cpp 
    lib/qtmaterialstatetransition.cpp 
    lib/qtmaterialstyle.cpp 
    lib/qtmaterialtheme.cpp 
    tools/qtmaterializer.cpp 
    tools/materializer/qtmaterializerlabel.cpp 
    tools/qtmaterialthemebuilder.cpp 
    qtmaterialappbar.cpp 
    qtmaterialappbar_internal.cpp 
    qtmaterialautocomplete.cpp 
    qtmaterialautocomplete_internal.cpp 
    qtmaterialavatar.cpp 
    qtmaterialbadge.cpp 
    qtmaterialbuttonlist.cpp 
    qtmaterialcanvas.cpp 
    qtmaterialcheckbox.cpp 
    qtmaterialcircularprogress.cpp 
    qtmaterialcircularprogress_internal.cpp 
    qtmaterialdialog.cpp 
    qtmaterialdialog_internal.cpp 
    qtmaterialdrawer.cpp 
    qtmaterialdrawer_internal.cpp 
    qtmaterialfab.cpp 
    qtmaterialflatbutton.cpp 
    qtmaterialflatbutton_internal.cpp 
    qtmaterialiconbutton.cpp 
    qtmateriallabel.cpp 
    qtmaterialpaper.cpp 
    qtmaterialprogress.cpp 
    qtmaterialprogress_internal.cpp 
    qtmaterialradiobutton.cpp 
    qtmaterialscrollbar.cpp 
    qtmaterialscrollbar_internal.cpp 
    qtmaterialslider.cpp 
    qtmaterialslider_internal.cpp 
    qtmaterialsnackbar.cpp 
    qtmaterialsnackbar_internal.cpp 
    qtmaterialsystembar.cpp 
    qtmaterialswitch.cpp 
    qtmaterialswitch_internal.cpp 
    qtmaterialtabs.cpp 
    qtmaterialtabs_internal.cpp 
    qtmaterialtextfield.cpp 
    qtmaterialtextfield_internal.cpp 
    qtmaterialwidget.cpp)
set(HEADERS 
    layouts/qtmaterialslidelayout.h 
    layouts/qtmaterialslidelayout_p.h 
    lib/qtmaterialcheckable.h 
    lib/qtmaterialcheckable_internal.h 
    lib/qtmaterialcheckable_p.h 
    lib/qtmaterialoverlaywidget.h 
    lib/qtmaterialripple.h 
    lib/qtmaterialrippleoverlay.h 
    lib/qtmaterialstatetransitionevent.h 
    lib/qtmaterialstatetransition.h 
    lib/qtmaterialstyle.h 
    lib/qtmaterialstyle_p.h 
    lib/qtmaterialtheme.h 
    lib/qtmaterialtheme_p.h 
    tools/qtmaterializer.h 
    tools/materializer/qtmaterializerlabel.h 
    tools/qtmaterialthemebuilder.h 
    qtmaterialappbar.h 
    qtmaterialappbar_internal.h 
    qtmaterialappbar_p.h 
    qtmaterialautocomplete.h 
    qtmaterialautocomplete_internal.h 
    qtmaterialautocomplete_p.h 
    qtmaterialavatar.h 
    qtmaterialavatar_p.h 
    qtmaterialbadge.h 
    qtmaterialbadge_p.h 
    qtmaterialbuttonlist.h 
    qtmaterialbuttonlist_p.h 
    qtmaterialcanvas.h 
    qtmaterialcanvas_p.h 
    qtmaterialcheckbox.h 
    qtmaterialcheckbox_p.h 
    qtmaterialcircularprogress.h 
    qtmaterialcircularprogress_internal.h 
    qtmaterialcircularprogress_p.h 
    qtmaterialdialog.h 
    qtmaterialdialog_internal.h 
    qtmaterialdialog_p.h 
    qtmaterialdrawer.h 
    qtmaterialdrawer_internal.h 
    qtmaterialdrawer_p.h 
    qtmaterialfab.h 
    qtmaterialfab_p.h 
    qtmaterialflatbutton.h 
    qtmaterialflatbutton_internal.h 
    qtmaterialflatbutton_p.h 
    qtmaterialiconbutton.h 
    qtmaterialiconbutton_p.h 
    qtmateriallabel.h 
    qtmateriallabel_p.h 
    qtmaterialpaper.h 
    qtmaterialpaper_p.h 
    qtmaterialprogress.h 
    qtmaterialprogress_internal.h 
    qtmaterialprogress_p.h 
    qtmaterialradiobutton.h 
    qtmaterialradiobutton_p.h 
    qtmaterialscrollbar.h 
    qtmaterialscrollbar_internal.h 
    qtmaterialscrollbar_p.h 
    qtmaterialslider.h 
    qtmaterialslider_internal.h 
    qtmaterialslider_p.h 
    qtmaterialsnackbar.h 
    qtmaterialsnackbar_internal.h 
    qtmaterialsnackbar_p.h 
    qtmaterialsystembar.h 
    qtmaterialsystembar_p.h 
    qtmaterialswitch.h 
    qtmaterialswitch_internal.h 
    qtmaterialswitch_p.h 
    qtmaterialtabs.h 
    qtmaterialtabs_internal.h 
    qtmaterialtabs_p.h 
    qtmaterialtextfield.h 
    qtmaterialtextfield_internal.h 
    qtmaterialtextfield_p.h 
    qtmaterialwidget.h 
    qtmaterialwidget_p.h 
    qtmaterialwidgets.h)

set(RESOURCES
resources.qrc
)

if(${QT_MATERIAL_WIDGETS_BUILD_STATIC})
    add_library(${LIB_TARGET_NAME} STATIC)
else()
    add_library(${LIB_TARGET_NAME} SHARED)
    target_compile_definitions(${LIB_TARGET_NAME} PRIVATE QTMATERIALWIDGETS_EXPORT_LIB)
endif()

add_library(${PROJECT_NAMESPACE}::${LIB_TARGET_NAME} ALIAS ${LIB_TARGET_NAME})

target_sources(${LIB_TARGET_NAME}
  PRIVATE
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
)

target_include_directories(${LIB_TARGET_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(${LIB_TARGET_NAME} PRIVATE ${QT_LIBRARIES})


set_target_properties(${LIB_TARGET_NAME}
  PROPERTIES
    AUTOMOC         ON
    AUTORCC         ON
    OUTPUT_NAME     ${LIB_TARGET_NAME}
    PROJECT_LABEL   ${LIB_TARGET_NAME}
    FOLDER          lib
    SOVERSION       ${PROJECT_VERSION_MAJOR}
    VERSION         ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    DEBUG_POSTFIX   _debug
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
  ${HEADERS}
  ${SOURCES}
)