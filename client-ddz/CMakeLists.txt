cmake_minimum_required(VERSION 3.16)
project(client-ddz VERSION 0.1 LANGUAGES CXX)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)
qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

set(PROJECT_SOURCES
    main.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/card
    ${PROJECT_SOURCE_DIR}/windows
    ${PROJECT_SOURCE_DIR}/control
    ${PROJECT_SOURCE_DIR}/player
    ${PROJECT_SOURCE_DIR}/strategy
    ${PROJECT_SOURCE_DIR}/thread
    ${PROJECT_SOURCE_DIR}/tcp
    ${PROJECT_SOURCE_DIR}/serialize
    ${PROJECT_SOURCE_DIR}/crypto
    "C:/OpenSSL-Win64/include"
    "C:/Protobuf/include"
)

link_directories("C:\\Protobuf\\lib")

add_subdirectory(card)
add_subdirectory(windows)
add_subdirectory(control)
add_subdirectory(player)
add_subdirectory(strategy)
add_subdirectory(thread)
add_subdirectory(tcp)
add_subdirectory(serialize)
add_subdirectory(crypto)

qt_add_resources(RES
    res.qrc
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    enable_language(RC)
    set(ICON_RES ${CMAKE_CURRENT_SOURCE_DIR}/ddz.rc)
endif()

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(client-ddz
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${RES}
        ${ICON_RES}
    )
else()
    if(ANDROID)
        add_library(client-ddz SHARED
            ${PROJECT_SOURCES}
            ${RES}
            ${ICON_RES}
        )
    else()
        add_executable(client-ddz
            ${PROJECT_SOURCES}
            ${RES}
            ${ICON_RES}
        )
    endif()
endif()

target_link_libraries(client-ddz PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    card
    windows
    control
    player
    strategy
    thread
    crypto
    serialize
    tcp
)

set_target_properties(client-ddz PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS client-ddz
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(client-ddz)
endif()

qt_generate_deploy_app_script(
    TARGET client-ddz
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
