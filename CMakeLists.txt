cmake_minimum_required(VERSION 3.12.0)

project(qt-material-widgets 
LANGUAGES CXX
VERSION 1.0.0.0)

option(QT_MATERIAL_WIDGETS_BUILD_EXAMPLES "Build examples" ON)

if(NOT QT_DEFAULT_MAJOR_VERSION)
    set(QT_DEFAULT_MAJOR_VERSION 5 CACHE STRING "Qt version to use (5 or 6), defaults to 5")
endif()

# Find dependencies
set(QT_COMPONENTS Core Widgets)
set(QT_LIBRARIES Qt${QT_DEFAULT_MAJOR_VERSION}::Core Qt${QT_DEFAULT_MAJOR_VERSION}::Widgets)


if(${QT_DEFAULT_MAJOR_VERSION} STREQUAL 6)
list(APPEND QT_COMPONENTS  StateMachine)
list(APPEND QT_LIBRARIES  Qt${QT_DEFAULT_MAJOR_VERSION}::StateMachine)
endif()


find_package(Qt${QT_DEFAULT_MAJOR_VERSION} COMPONENTS ${QT_COMPONENTS} REQUIRED)


add_subdirectory(components)

if(QT_MATERIAL_WIDGETS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
