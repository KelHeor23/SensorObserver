cmake_minimum_required(VERSION 3.5)

project(SensorObserver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SensorObserver
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SensorObserver APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SensorObserver SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SensorObserver
            ${PROJECT_SOURCES}
            Widgets/MainWindow.h Widgets/MainWindow.cpp
            Exchange/Client.h Exchange/Client.cpp
            Widgets/SensorsTable/ListOfLimits.h Widgets/SensorsTable/ListOfLimits.cpp
            Widgets/SensorsTable/DisplayingSensors.h Widgets/SensorsTable/DisplayingSensors.cpp
            Widgets/SensorsTable/VibrationDirection.h Widgets/SensorsTable/VibrationDirection.cpp
            Exchange/Protocols/EngineSensors/EngineSensors.h Exchange/Protocols/EngineSensors/EngineSensors.cpp
            Exchange/Protocols/Sensors.h
            Exchange/Protocols/VoltageRegulators/VoltageRegulators.h Exchange/Protocols/VoltageRegulators/VoltageRegulators.cpp
            Widgets/SensorsTable/SensorsTableWidget.h Widgets/SensorsTable/SensorsTableWidget.cpp
            Common/Common.h
            Exchange/Protocols/Constants.h
            Tools/ColorProgressBar.h Tools/ColorProgressBar.cpp
            Exchange/Protocols/EscSensors/Frames.h
            Exchange/Protocols/EscSensors/EscSensors.h Exchange/Protocols/EscSensors/EscSensors.cpp
            Widgets/SensorsTable/ListOfLimitsWidget.h Widgets/SensorsTable/ListOfLimitsWidget.cpp
            Exchange/Protocols/Base.h
        )
    endif()
endif()

target_link_libraries(SensorObserver PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
target_include_directories(SensorObserver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SensorObserver)
endif()
set_target_properties(SensorObserver PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SensorObserver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SensorObserver)
endif()
