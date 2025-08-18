cmake_minimum_required(VERSION 3.5)

project(SensorObserver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network PrintSupport)

set(PROJECT_SOURCES
        main.cpp
        Widgets/MainWindow.h Widgets/MainWindow.cpp
        Widgets/SensorsTable/DisplayingSensors.h Widgets/SensorsTable/DisplayingSensors.cpp
        Widgets/SensorsTable/VibrationDirection.h Widgets/SensorsTable/VibrationDirection.cpp
        Widgets/SensorsTable/ListOfLimitsWidget.h Widgets/SensorsTable/ListOfLimitsWidget.cpp
        Widgets/SensorsTable/DetailingLimitsWidget.h Widgets/SensorsTable/DetailingLimitsWidget.cpp
        Widgets/SensorsTable/SensorsTableWidget.h Widgets/SensorsTable/SensorsTableWidget.cpp
        Widgets/Common/ConnSettings.h Widgets/Common/ConnSettings.cpp
        Widgets/Other/MotorControl.h Widgets/Other/MotorControl.cpp
        Widgets/Other/SmoothMotorControl.h Widgets/Other/SmoothMotorControl.cpp
        Widgets/SensorDataGraph/SensorDataGraph.cpp Widgets/SensorDataGraph/SensorDataGraph.h
        Common/Common.h
        Tools/ColorButton.h Tools/ColorButton.cpp
        Tools/ColorProgressBar.h Tools/ColorProgressBar.cpp
        Tools/CollapsibleGroupBox.h Tools/CollapsibleGroupBox.cpp
        Tools/SaveToCSV.h Tools/SaveToCSV.cpp
        Tools/ValueIncrementer.h Tools/ValueIncrementer.cpp
        Exchange/Client.h Exchange/Client.cpp
        Data/DataStructure.cpp Data/DataStructure.h
        Data/Frames.h
        Libs/QCustomPlot/qcustomplot.cpp Libs/QCustomPlot/qcustomplot.h
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
        )
    endif()
endif()

target_include_directories(SensorObserver PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/Libs/QCustomPlot")

target_link_libraries(SensorObserver PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::PrintSupport)

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
