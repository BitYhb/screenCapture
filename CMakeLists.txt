cmake_minimum_required(VERSION 3.5)

project(untitled4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5
    COMPONENTS
    Widgets
    Network
    Gui
    REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
    Widgets
    Network
    Gui
    REQUIRED)
set(PROJECT_SOURCES
        "main.cpp"
        "src/widget.cpp"
        "src/widget.h"
        "src/screencapture.cpp"
        "src/screencapture.h"
        "src/decodevideo.cpp"
        "src/decodevideo.h"
        "src/partarea.cpp"
        "src/partarea.h"
        "src/screencapturefactory.cpp"
        "src/screencapturefactory.h"
)

set(ffmpeg_DIR "${PROJECT_SOURCE_DIR}/3rdpart/ffmpeg4.4.1/")
if(NOT ffmpeg_DIR)
    message(FATAL_ERROR "ffmpeg_DIR must be set")
endif()
include_directories(${ffmpeg_DIR}/include/)
link_directories(${ffmpeg_DIR}/lib/)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(untitled4
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled4 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(untitled4 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(untitled4
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Gui
    swscale
    avcodec
    avdevice
    avfilter
    avformat
    avutil
    postproc
    swresample
    )

set_target_properties(untitled4 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(untitled4)
endif()
