#===============================================================================
# Editable project configuration
#
# Essential, non translatable application information (except DESCRIPTION).
# translatable strings are passed via code.
#===============================================================================
string(TOLOWER ${PROJECT_NAME} PROJECT_ID)   # Might not be compatible with AppStream
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND PROJECT_CATEGORIES "Qt;Utility") # Freedesktop menu categories
set(PROJECT_AUTHOR_NAME        "Andrea Zanellato")
set(PROJECT_AUTHOR_EMAIL       "redtid3@gmail.com") # Used also for organization email
set(PROJECT_COPYRIGHT_YEAR     "2021-2023") # TODO: from git
set(PROJECT_DESCRIPTION        "Simple ruler tool in Qt")
set(PROJECT_HOMEPAGE_URL       "http://qtilities.github.io/qruler")
set(PROJECT_ICON_FORMAT        "svg")       # TODO: macOS and Windows
set(PROJECT_ORGANIZATION_NAME  "qtilities") # Might be equal to PROJECT_AUTHOR_NAME
set(PROJECT_ORGANIZATION_URL   "${PROJECT_ORGANIZATION_NAME}.github.io")
set(PROJECT_REPOSITORY_URL     "https://github.com/${PROJECT_ORGANIZATION_NAME}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_BRANCH  "master")
set(PROJECT_SPDX_ID            "GPL-3.0-only")
#===============================================================================
# Appstream
#===============================================================================
set(PROJECT_APPSTREAM_SPDX_ID  "CC0-1.0")
include(AppStream)
to_appstream_id("io.github.${PROJECT_ORGANIZATION_NAME}.${PROJECT_ID}"
    PROJECT_APPSTREAM_ID)
