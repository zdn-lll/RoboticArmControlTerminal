cmake_minimum_required(VERSION 3.5)

project(RoboticArmControlTerminal_v3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)

add_subdirectory(src)

include_directories(${CMAKE_SOURCE_DIR}/src/include)
include_directories(${CMAKE_SOURCE_DIR}/src/private)
include_directories(${CMAKE_SOURCE_DIR}/src/DeveloperComponents)
include_directories(${CMAKE_SOURCE_DIR}/FeaturesPage)
include_directories(${CMAKE_SOURCE_DIR}/Function)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RoboticArmControlTerminal_v3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        FeaturesPage/about.cpp FeaturesPage/about.h FeaturesPage/gyroscopepage.cpp FeaturesPage/gyroscopepage.h FeaturesPage/homepage.cpp FeaturesPage/homepage.h FeaturesPage/roboticarmpage.cpp FeaturesPage/roboticarmpage.h FeaturesPage/serialportassistantpage.cpp FeaturesPage/serialportassistantpage.h
        Function/robotarm.cpp Function/robotarm.h
        res.qrc
        Function/movesettableview.h Function/movesettableview.cpp
        Function/communicationprotocols.h Function/communicationprotocols.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RoboticArmControlTerminal_v3 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RoboticArmControlTerminal_v3 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RoboticArmControlTerminal_v3
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(RoboticArmControlTerminal_v3 PRIVATE elawidgettools)
target_link_libraries(RoboticArmControlTerminal_v3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(RoboticArmControlTerminal_v3 PRIVATE Qt6::SerialPort)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RoboticArmControlTerminal_v3)
endif()
set_target_properties(RoboticArmControlTerminal_v3 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS RoboticArmControlTerminal_v3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RoboticArmControlTerminal_v3)
endif()
