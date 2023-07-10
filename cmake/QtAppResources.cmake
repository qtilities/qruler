#===============================================================================
# QtAppResources.cmake
#
# Configure and Installs:
# - About information markdown file
# - Appstream metainfo
# - Desktop file
# - Translation files via lxqt-build-tools
#
#   TODO: Windows and macOS
#===============================================================================
# Configure files
#===============================================================================
if (UNIX AND NOT APPLE)
    include(GNUInstallDirs)
    # "resources/about.md" is a gitignored file configured by cmake and then added
    # to the Qt resource file, so not needed in the build directory.
    configure_file("resources/in/about.info.md.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/about.md" @ONLY
    )
    # TODO :Create a "description.html" file from PROJECT_DESCRIPTION
    #       And insert its content into "PROJECT_APPDATA_FILE", see
    # (https://freedesktop.org/software/appstream/docs/chap-Metadata.html#tag-description)
    # and a git tags string list from function to PROJECT_RELEASES variable
    # (https://freedesktop.org/software/appstream/docs/chap-Metadata.html#tag-releases)
    set(PROJECT_APPDATA_FILE_NAME "${PROJECT_APPSTREAM_ID}.appdata.xml")
    configure_file("resources/in/linux/application.appdata.xml.in"
        "${PROJECT_APPDATA_FILE_NAME}" @ONLY
    )
    # TODO: This file needs to be processed first by `configure_file()` for `@` variables,
    # then the resulting file, the one below, to be processed by `lxqt_translate_desktop`.
    # Would be better doing this in one step in `lxqt_translate_desktop` only.
    set(DESKTOP_FILE_IN "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_APPSTREAM_ID}.desktop.in")
    configure_file("resources/in/linux/application.desktop.in"
        "${DESKTOP_FILE_IN}" @ONLY
    )
    set(PROJECT_ICON_FILE_NAME "${PROJECT_APPSTREAM_ID}.${PROJECT_ICON_FORMAT}")
    set(PROJECT_ICON_FILE_PATH "${CMAKE_INSTALL_FULL_DATADIR}/icons/hicolor/scalable/apps")
    configure_file("resources/icons/application.icon.${PROJECT_ICON_FORMAT}"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_ICON_FILE_NAME}" COPYONLY
    )
    #===========================================================================
    # Translations
    #===========================================================================
    # TODO: Search in PATH
    set(LXQT_CMAKE_MODULES_DIR "/usr/share/cmake/lxqt-build-tools/modules")
    list(APPEND CMAKE_MODULE_PATH ${LXQT_CMAKE_MODULES_DIR})

    option(UPDATE_TRANSLATIONS "Update source translation files" OFF)

    # TODO: include(LXQtPreventInSourceBuilds) ???
    include(LXQtTranslateDesktop)
    include(LXQtTranslateTs)

    lxqt_translate_ts(PROJECT_QM_FILES
        UPDATE_TRANSLATIONS ${UPDATE_TRANSLATIONS}
        SOURCES             ${PROJECT_SOURCES} ${PROJECT_UI_FILES}
        TRANSLATION_DIR     "resources/translations"
        INSTALL_DIR         "${CMAKE_INSTALL_DATADIR}/${PROJECT_ID}/translations"
    )
    lxqt_translate_desktop(PROJECT_DESKTOP_FILES
        SOURCES             "${DESKTOP_FILE_IN}"
        TRANSLATION_DIR     "resources/translations"
        USE_YAML
    )
#===============================================================================
# Install
#===============================================================================
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_APPDATA_FILE_NAME}"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/metainfo"
    )
    install(FILES "${PROJECT_DESKTOP_FILES}"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/applications"
    )
endif()
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_ICON_FILE_NAME}"
    DESTINATION "${PROJECT_ICON_FILE_PATH}"
)
