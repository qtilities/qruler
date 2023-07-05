# Installs:
# - translation files via lxqt-build-tools
# - application' desktop file
# - application' icon
# - appstream metainfo

# LXQt build tools modules
if (UNIX AND NOT APPLE)
    include(GNUInstallDirs)
    # TODO: Search in PATH
    set(LXQT_CMAKE_MODULES_DIR "/usr/share/cmake/lxqt-build-tools/modules")
    list(APPEND CMAKE_MODULE_PATH ${LXQT_CMAKE_MODULES_DIR})
else()
    # TODO: Windows and macOS
endif()

# Translations
option(UPDATE_TRANSLATIONS "Update source translation files" OFF)

include(LXQtPreventInSourceBuilds)
include(LXQtTranslateDesktop)
include(LXQtTranslateTs)
include(LXQtTranslationLoader)


if (UNIX AND NOT APPLE)
    set(BUILD_DATADIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_DATADIR}")
    set(BUILD_BINDIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
    # TODO :Assign a "description.html file" content to PROJECT_DESCRIPTION variable
    # (https://freedesktop.org/software/appstream/docs/chap-Metadata.html#tag-description)
    # and a git tags string list from function to PROJECT_RELEASES variable
    # (https://freedesktop.org/software/appstream/docs/chap-Metadata.html#tag-releases)
    set(APPICON_FILE_SRC "resources/icons/application.icon.${PROJECT_ICON_FORMAT}")
    set(APPDATA_FILE_IN  "resources/in/linux/application.appdata.xml.in")
    set(DESKTOP_FILE_IN  "resources/in/linux/application.desktop.in")

    set(APPICON_FILE_NAME "${PROJECT_APPSTREAM_ID}.${PROJECT_ICON_FORMAT}")
    set(APPICON_FILE_BUILD_PATH "${BUILD_DATADIR}/icons/hicolor/scalable/apps/${APPICON_FILE_NAME}")
    set(APPDATA_FILE_BUILD_PATH "${BUILD_DATADIR}/metainfo/${PROJECT_APPSTREAM_ID}.appdata.xml")
    # TODO: This file needs to be processed first by `configure_file()` for `@` variables,
    # then the resulting file, the one below, to be processed by `lxqt_translate_desktop`.
    # Would be better doing this in one step in `lxqt_translate_desktop` only.
    set(DESKTOP_FILE_BUILD_PATH "${BUILD_DATADIR}/applications/${PROJECT_APPSTREAM_ID}.desktop.in")

    message(STATUS "APPDATA_FILE_BUILD_PATH:  ${APPDATA_FILE_BUILD_PATH}")
    message(STATUS "APPICON_FILE_BUILD_PATH:  ${APPICON_FILE_BUILD_PATH}")
    message(STATUS "DESKTOP_FILE_BUILD_PATH:  ${DESKTOP_FILE_BUILD_PATH}")

    configure_file(${APPDATA_FILE_IN}  "${APPDATA_FILE_BUILD_PATH}" @ONLY)
    configure_file(${APPICON_FILE_SRC} "${APPICON_FILE_BUILD_PATH}" COPYONLY @ONLY)
    configure_file(${DESKTOP_FILE_IN}  "${DESKTOP_FILE_BUILD_PATH}" @ONLY)
endif()

# APPINFO_FILE_OUT is a gitignored file configured by cmake and then added
# to the Qt resource file, so not needed in build directory
set(APPINFO_FILE_IN  "resources/in/about.info.md.in")
set(APPINFO_FILE_OUT "${CMAKE_CURRENT_SOURCE_DIR}/resources/about.md")
configure_file(${APPINFO_FILE_IN} ${APPINFO_FILE_OUT} @ONLY)

# TRANSLATION_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/resources/translations"
lxqt_translate_ts(PROJECT_QM_FILES
    UPDATE_TRANSLATIONS ${UPDATE_TRANSLATIONS}
    SOURCES             ${PROJECT_SOURCES}
    TRANSLATION_DIR     "resources/translations"
    INSTALL_DIR         "${CMAKE_INSTALL_DATADIR}/${PROJECT_ID}/translations"
)
lxqt_translate_desktop(PROJECT_DESKTOP_FILE
    SOURCES             "${DESKTOP_FILE_BUILD_PATH}"
    TRANSLATION_DIR     "resources/translations"
    USE_YAML
)
lxqt_app_translation_loader(SOURCES ${PROJECT_NAME})

# Other resources
if (UNIX AND NOT APPLE)
    install(FILES "${APPDATA_FILE_BUILD_PATH}"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/metainfo"
    )
    install(FILES "${APPICON_FILE_BUILD_PATH}"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps"
        RENAME "${APPICON_FILE_NAME}"
    )
    install(FILES "${PROJECT_DESKTOP_FILE}"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
    )
endif()
