# Installs:
# - translation files via lxqt-build-tools
# - application' desktop file
# - application' icon
# - appstream metainfo

# LXQt build tools modules
if (UNIX AND NOT APPLE)
    include(GNUInstallDirs)
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
    set(APPDATA_FILE_IN
        "resources/linux/${PROJECT_APPSTREAM_ID}.appdata.xml.in"
    )
    set(APPDATA_FILE_OUT
        "${PROJECT_APPSTREAM_ID}.appdata.xml"
    )
    set(DESKTOP_FILE_IN
        resources/linux/${PROJECT_APPSTREAM_ID}.desktop.in
    )
    # TODO
    # - Assign a description.html file content to PROJECT_DESCRIPTION variable
    # - Git tags array from function to PROJECT_RELEASES variable

    configure_file(
        ${APPDATA_FILE_IN}
        ${APPDATA_FILE_OUT}
    )
endif()

# TRANSLATION_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/resources/translations"
lxqt_translate_ts(QM_FILES
    UPDATE_TRANSLATIONS ${UPDATE_TRANSLATIONS}
    SOURCES             ${PROJECT_FILES}
    TRANSLATION_DIR     "resources/translations"
    INSTALL_DIR         "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_ID}/translations"
)
lxqt_translate_desktop(DESKTOP_FILES
    SOURCES             "${CMAKE_CURRENT_SOURCE_DIR}/${DESKTOP_FILE_IN}"
    TRANSLATION_DIR     "resources/translations"
    USE_YAML
)
lxqt_app_translation_loader(SOURCES ${PROJECT_NAME})

# Other resources
if (UNIX AND NOT APPLE)
    install(FILES "resources/icons/${PROJECT_APPSTREAM_ID}.svg"
        DESTINATION "${CMAKE_INSTALL_FULL_DATADIR}/icons/hicolor/scalable/apps"
    )
    install(FILES "${DESKTOP_FILES}"
        DESTINATION "${CMAKE_INSTALL_FULL_DATADIR}/applications"
    )
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${APPDATA_FILE_OUT}"
        DESTINATION "${CMAKE_INSTALL_FULL_DATADIR}/metainfo"
    )
endif()
