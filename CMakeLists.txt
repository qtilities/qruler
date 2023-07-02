cmake_minimum_required(VERSION 3.15)
project(
    QRuler
    DESCRIPTION  "Simple ruler tool in Qt"
    HOMEPAGE_URL "http://qtilities.github.io/qruler"
    VERSION 0.1.1
    LANGUAGES CXX
)
string(TOLOWER ${PROJECT_NAME} PROJECT_ID)
set(PROJECT_APPSTREAM_ID       "io.github.qtilities.${PROJECT_ID}")
set(PROJECT_APPSTREAM_SPDX_ID  "CC0-1.0")
set(PROJECT_AUTHOR_NAME        "redtide")
set(PROJECT_AUTHOR_EMAIL       "redtid3@gmail.com")
set(PROJECT_REPOSITORY_URL     "https://github.com/qtilities/${PROJECT_ID}")
set(PROJECT_REPOSITORY_BRANCH  "master")
set(PROJECT_SPDX_ID            "GPL-3.0-only")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
#===============================================================================
# Source and resource files
#===============================================================================
set(RESOURCE_FILES
    resources/resources.qrc
)
set(UI_FILES
    src/dialogprefs.ui
)
set(PROJECT_FILES
    src/dialogprefs.hpp
    src/dialogprefs.cpp
    src/qruler.hpp
    src/qruler.cpp
    src/settings.hpp
    src/settings.cpp
    src/application.hpp
    src/application.cpp
    ${UI_FILES}
)
include(QtAppResources)

qt5_wrap_ui(UI_SOURCE ${UI_FILES})
set_property(SOURCE ${UI_SOURCE} PROPERTY SKIP_AUTOMOC ON)
#===============================================================================
# Application executable
#===============================================================================
add_executable(${PROJECT_NAME}
    ${DESKTOP_FILES}
    ${PROJECT_FILES}
    ${RESOURCE_FILES}
    ${QM_FILES}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Widgets
)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_ID}")
#===============================================================================
# Install application
#===============================================================================
if (UNIX AND NOT APPLE)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
#===============================================================================
# Project information
#===============================================================================
message(STATUS "
Project name:                     ${CMAKE_PROJECT_NAME}
Version:                          ${CMAKE_PROJECT_VERSION}
Build type:                       ${CMAKE_BUILD_TYPE}
Install prefix:                   ${CMAKE_INSTALL_PREFIX}
Update translations before build: ${UPDATE_TRANSLATIONS}

Qt version:                       ${Qt5Core_VERSION_STRING}

CXX Debug flags:                  ${CMAKE_CXX_FLAGS_DEBUG}
CXX Release flags:                ${CMAKE_CXX_FLAGS_RELEASE}
CXX MinSize flags:                ${CMAKE_CXX_FLAGS_MINSIZEREL}
CXX RelWithDebInfo flags:         ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}
")
