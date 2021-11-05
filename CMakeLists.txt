cmake_minimum_required(VERSION 3.6)
project(QRuler VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES resources/translations/qruler_it_IT.ts)

set(SRC_FILES
    src/dialogprefs.hpp
    src/dialogprefs.cpp
    src/dialogprefs.ui
    src/qruler.hpp
    src/qruler.cpp
    src/settings.hpp
    src/settings.cpp
    src/application.hpp
    src/application.cpp
    resources/resources.qrc
    ${TS_FILES}
)
add_executable(${CMAKE_PROJECT_NAME}
    ${SRC_FILES}
)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt5::Widgets
)
if (UNIX AND NOT APPLE)
    string(TOLOWER ${CMAKE_PROJECT_NAME} APP_NAME)
    set(APPSTREAM_BASENAME "org.azdrums.${APP_NAME}")
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "${APP_NAME}"
    )
    include (GNUInstallDirs)
    install (TARGETS ${CMAKE_PROJECT_NAME}
        DESTINATION ${CMAKE_INSTALL_BINDIR})
    install (FILES resources/icons/${APP_NAME}.svg
        DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps)
    install (FILES resources/linux/${APPSTREAM_BASENAME}.appdata.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)
    install (FILES resources/linux/${APPSTREAM_BASENAME}.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
#   install (FILES ${QM_FILES}
#       DESTINATION ${CMAKE_INSTALL_PREFIX}/share/${APP_NAME}/translations)
endif()
