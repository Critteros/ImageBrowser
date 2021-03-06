cmake_minimum_required(VERSION 3.22)
project(ImageBrowser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

qt_standard_project_setup()

#find_package(exiv2 REQUIRED CONFIG NAMES exiv2)
set(ZLIB_ROOT "${CMAKE_CURRENT_LIST_DIR}/dependencies/zlib")
find_package(ZLIB REQUIRED)
add_subdirectory(dependencies)
include_directories("include")

file(GLOB includes include/*.hpp)
file(GLOB sources src/*.cpp)

qt_add_executable(ImageBrowser imagebrowser.qrc ${includes} ${sources} icon.rc)
#qt_add_executable(ImageBrowser src/main.cpp)
target_link_libraries(ImageBrowser PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        dependencies
        ZLIB::ZLIB
        Psapi.lib
        )

if (MSVC)

    target_link_options(ImageBrowser PRIVATE /FORCE:MULTIPLE)

endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET ImageBrowser PROPERTY WIN32_EXECUTABLE true)
endif ()

#target_compile_definitions(ImageBrowser PRIVATE $<$<CONFIG:Debug>:_CRTDBG_MAP_ALLOC>>)

#if (WIN32)
#    set(DEBUG_SUFFIX)
#    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
#        set(DEBUG_SUFFIX "d")
#    endif ()
#    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
#    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
#            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        endif ()
#    endif ()
#    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E make_directory
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#    endif ()
#    foreach (QT_LIB Core Gui Widgets)
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
#    endforeach (QT_LIB)
#endif ()
