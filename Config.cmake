#===============================================================================
# Editable project configuration
#
# Essential, non translatable application information (except DESCRIPTION).
# Translatable strings are passed via code.
#===============================================================================
string(TOLOWER ${PROJECT_NAME} PROJECT_ID)
list(APPEND PROJECT_CATEGORIES "Qt;Utility") # Freedesktop menu categories
list(APPEND PROJECT_KEYWORDS   "screen;ruler")
set(PROJECT_AUTHOR_NAME        "Andrea Zanellato")
set(PROJECT_AUTHOR_EMAIL       "redtid3@gmail.com") # Used also for organization email
set(PROJECT_COPYRIGHT_YEAR     "2021-2023")  # TODO: from git
set(PROJECT_DESCRIPTION        "Simple ruler tool in Qt")
set(PROJECT_ORGANIZATION_NAME  "qtilities")  # Might be equal to PROJECT_AUTHOR_NAME
set(PROJECT_ORGANIZATION_URL   "${PROJECT_ORGANIZATION_NAME}.github.io")
set(PROJECT_HOMEPAGE_URL       "https://${PROJECT_ORGANIZATION_URL}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_URL     "https://github.com/${PROJECT_ORGANIZATION_NAME}/${PROJECT_ID}")
set(PROJECT_REPOSITORY_BRANCH  "master")
set(PROJECT_SPDX_ID            "GPL-3.0-only")
set(PROJECT_TRANSLATIONS_DIR   "resources/translations")
#===============================================================================
# Appstream
#===============================================================================
set(PROJECT_APPSTREAM_SPDX_ID  "FSFAP")
include(AppStream)
to_appstream_id("io.github.${PROJECT_ORGANIZATION_NAME}.${PROJECT_NAME}"
    PROJECT_APPSTREAM_ID)

set(PROJECT_ICON_FORMAT        "svg")
if(UNIX AND NOT APPLE)
    set(PROJECT_ICON_FILE_NAME "${PROJECT_APPSTREAM_ID}.${PROJECT_ICON_FORMAT}")
elseif(APPLE)
    # TODO: macOS and Windows
else()
endif()
#===============================================================================
# Adapt to CMake variables
#===============================================================================
set(${PROJECT_NAME}_DESCRIPTION  "${PROJECT_DESCRIPTION}")
set(${PROJECT_NAME}_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
