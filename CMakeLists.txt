cmake_minimum_required(VERSION 3.15)
project(
    QRuler
    DESCRIPTION  "Simple ruler tool in Qt"
    HOMEPAGE_URL "http://qtilities.github.io/qruler"
    VERSION 0.1.1
    LANGUAGES CXX
)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

# TODO: Qt6
#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

include(AppStream)
# Essential, non translatable application information
# Translatable strings are passed via code
string(TOLOWER ${PROJECT_NAME} PROJECT_ID)   # Might not be compatible with AppStream
list(APPEND PROJECT_CATEGORIES "Qt;Utility") # Freedesktop menu categories
set(PROJECT_AUTHOR_NAME        "redtide")
set(PROJECT_AUTHOR_EMAIL       "redtid3@gmail.com") # Used also for organization email
set(PROJECT_COPYRIGHT_YEAR     "2021-2023") # TODO: from git
set(PROJECT_ICON_FORMAT        "svg")       # TODO: macOS and Windows
set(PROJECT_ORGANIZATION_NAME  "qtilities") # Might be equal to PROJECT_AUTHOR_NAME
set(PROJECT_ORGANIZATION_URL   "${PROJECT_ORGANIZATION_NAME}.github.io")
set(PROJECT_REPOSITORY_URL     "https://github.com/${PROJECT_ORGANIZATION_NAME}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_BRANCH  "master")
to_appstream_id("io.github.${PROJECT_ORGANIZATION_NAME}.${PROJECT_ID}"
    PROJECT_APPSTREAM_ID)
set(PROJECT_APPSTREAM_SPDX_ID  "CC0-1.0")
set(PROJECT_SPDX_ID            "GPL-3.0-only")
#===============================================================================
# Source and resource files
#===============================================================================
set(PROJECT_UI_FILES
    src/dialogabout.ui
    src/dialogprefs.ui
)
set(PROJECT_SOURCES
    src/application.hpp
    src/application.cpp
    src/dialogabout.hpp
    src/dialogabout.cpp
    src/dialogprefs.hpp
    src/dialogprefs.cpp
    src/mainwindow.hpp
    src/mainwindow.cpp
    src/settings.hpp
    src/settings.cpp
    ${PROJECT_UI_FILES}
)
set(PROJECT_MISC_FILES
    README.md
)
set(PROJECT_RESOURCES
    resources/resources.qrc
)
include(QtAppResources)
set(PROJECT_ALL_FILES
    ${PROJECT_DESKTOP_FILE}
    ${PROJECT_MISC_FILES}
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES}
    ${PROJECT_QM_FILES}
)
source_group("Resource Files" FILES ${PROJECT_RESOURCES})
source_group("Other Files" FILES ${PROJECT_MISC_FILES})
source_group("UI Files" FILES ${PROJECT_UI_FILES})

qt5_wrap_ui(PROJECT_UI_SOURCE ${PROJECT_UI_FILES})
set_property(SOURCE ${PROJECT_UI_SOURCE} PROPERTY SKIP_AUTOMOC ON)
#===============================================================================
# Application executable
#===============================================================================
# FIXME: QT_VERSION_MAJOR is not defined??
#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
if(false)
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET test APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_ALL_FILES})
#   qt_create_translation(PROJECT_QM_FILES ${CMAKE_SOURCE_DIR} ${PROJECT_TS_FILES})
else()
    if(ANDROID)
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
        add_library(${PROJECT_NAME} SHARED ${PROJECT_ALL_FILES})
    else()
        add_executable(${PROJECT_NAME} ${PROJECT_ALL_FILES})
    endif()
#   qt5_create_translation(PROJECT_QM_FILES ${CMAKE_SOURCE_DIR} ${PROJECT_TS_FILES})
endif()

if(false)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Widgets
)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_ID}")
target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        APPLICATION_NAME="${PROJECT_NAME}"
        ORGANIZATION_NAME="${PROJECT_ORGANIZATION_NAME}"
        ORGANIZATION_DOMAIN="${PROJECT_ORGANIZATION_URL}"
    PRIVATE
        PROJECT_ID="${PROJECT_ID}"
        PROJECT_DATA_DIR="${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_ID}"
        PROJECT_ICON_PATH="${APPICON_FILE_PATH}"
)
#===============================================================================
# Install application
#===============================================================================
if (UNIX AND NOT APPLE)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
else()
    set_target_properties(test PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER ${PROJECT_ORGANIZATION_URL}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )
    install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(test)
endif()
#===============================================================================
# Project information
#===============================================================================
message(STATUS "
Project name:                     ${PROJECT_NAME}
AppStream ID:                     ${PROJECT_APPSTREAM_ID}
Version:                          ${PROJECT_VERSION}
Qt version:                       ${Qt5Core_VERSION_STRING}
Build type:                       ${CMAKE_BUILD_TYPE}
Install prefix:                   ${CMAKE_INSTALL_PREFIX}
Update translations before build: ${UPDATE_TRANSLATIONS}

CXX Debug flags:                  ${CMAKE_CXX_FLAGS_DEBUG}
CXX Release flags:                ${CMAKE_CXX_FLAGS_RELEASE}
CXX MinSize flags:                ${CMAKE_CXX_FLAGS_MINSIZEREL}
CXX RelWithDebInfo flags:         ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}
")
