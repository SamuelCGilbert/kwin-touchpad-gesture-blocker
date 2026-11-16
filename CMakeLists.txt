cmake_minimum_required(VERSION 3.16)
project(kwin-touchpad-gesture-blocker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
add_compile_definitions(QT_NO_KEYWORDS)

find_package(Qt6 REQUIRED COMPONENTS Core Gui DBus Qml Widgets)
find_package(KF6Config REQUIRED)
find_package(KWin REQUIRED)

add_library(touchpadgestureblocker MODULE gestureblocker.cpp main.cpp)
set_target_properties(touchpadgestureblocker PROPERTIES PREFIX "")
target_link_libraries(touchpadgestureblocker PRIVATE KWin::kwin Qt6::Core Qt6::Gui Qt6::Qml KF6::ConfigCore)

if(NOT DEFINED KWIN_PLUGIN_INSTALL_DIR)
    get_target_property(_qmake Qt6::qmake IMPORTED_LOCATION)
    execute_process(COMMAND ${_qmake} -query QT_INSTALL_PLUGINS
                    OUTPUT_VARIABLE _qt_plugins OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(KWIN_PLUGIN_INSTALL_DIR "${_qt_plugins}/kwin/plugins")
endif()
install(TARGETS touchpadgestureblocker DESTINATION "${KWIN_PLUGIN_INSTALL_DIR}")
