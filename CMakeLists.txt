cmake_minimum_required(VERSION 3.16)

project(SensorObserver
  VERSION 0.1
  LANGUAGES CXX)

# ---- C++ / Qt базовые настройки ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Автоматическая обработка Qt-макросов/форм/ресурсов
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Предпочтительно Qt6, но допускаем Qt5.15+
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network PrintSupport)

# ---- Варианты предупреждений под компилятор ----
if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ---- Источники проекта ----
set(PROJECT_SOURCES
  main.cpp
  Widgets/MainWindow.h            Widgets/MainWindow.cpp

  Widgets/SensorsTable/DisplayingSensors.h     Widgets/SensorsTable/DisplayingSensors.cpp
  Widgets/SensorsTable/VibrationDirection.h    Widgets/SensorsTable/VibrationDirection.cpp
  Widgets/SensorsTable/ListOfLimitsWidget.h    Widgets/SensorsTable/ListOfLimitsWidget.cpp
  Widgets/SensorsTable/DetailingLimitsWidget.h Widgets/SensorsTable/DetailingLimitsWidget.cpp
  Widgets/SensorsTable/SensorsTableWidget.h    Widgets/SensorsTable/SensorsTableWidget.cpp

  Widgets/Common/ConnSettings.h   Widgets/Common/ConnSettings.cpp
  Widgets/Other/MotorControl.h    Widgets/Other/MotorControl.cpp
  Widgets/Other/SmoothMotorControl.h Widgets/Other/SmoothMotorControl.cpp

  Widgets/SensorDataGraph/SensorDataGraph.h Widgets/SensorDataGraph/SensorDataGraph.cpp

  Common/Common.h
  Data/CommonTypes.h

  Tools/ColorButton.h         Tools/ColorButton.cpp
  Tools/ColorProgressBar.h    Tools/ColorProgressBar.cpp
  Tools/CollapsibleGroupBox.h Tools/CollapsibleGroupBox.cpp
  Tools/SaveToCSV.h           Tools/SaveToCSV.cpp
  Tools/ValueIncrementer.h    Tools/ValueIncrementer.cpp

  Exchange/Client.h           Exchange/Client.cpp

  Data/DataStructure.h        Data/DataStructure.cpp

  Data/Frames/Containers/Base.h
  Data/Frames/Containers/Constants.h
  Data/Frames/Containers/Sensors.h
  Data/Frames/Containers/SensorSettingsManager.h Data/Frames/Containers/SensorSettingsManager.cpp
  Data/Frames/Containers/SensorsFrames.h        Data/Frames/Containers/SensorsFrames.cpp

  Data/Frames/Containers/EngineSensors/EngineSensors.h  Data/Frames/Containers/EngineSensors/EngineSensors.cpp
  Data/Frames/Containers/EscSensors/EscStatus1.h        Data/Frames/Containers/EscSensors/EscStatus1.cpp
  Data/Frames/Containers/EscSensors/EscStatus2.h        Data/Frames/Containers/EscSensors/EscStatus2.cpp
  Data/Frames/Containers/EscSensors/EscStatus3.h        Data/Frames/Containers/EscSensors/EscStatus3.cpp

  Data/Frames/Containers/VoltageRegulators/VoltageRegulators.h Data/Frames/Containers/VoltageRegulators/VoltageRegulators.cpp

  Data/Frames/Frames.h

  Libs/QCustomPlot/qcustomplot.h Libs/QCustomPlot/qcustomplot.cpp
)

# ---- Исполняемый файл ----
# На Windows создаём GUI-приложение (без консольного окна)
if(WIN32)
  add_executable(SensorObserver WIN32 ${PROJECT_SOURCES})
else()
  add_executable(SensorObserver     ${PROJECT_SOURCES})
endif()

# ---- Публичные include-директории ----
target_include_directories(SensorObserver
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Libs/QCustomPlot
)

# ---- Линки ----
target_link_libraries(SensorObserver
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

# Немного защиты от устаревших Qt-API (необязательно)
target_compile_definitions(SensorObserver
  PRIVATE
    QT_DISABLE_DEPRECATED_BEFORE=0x050F00 # запретить API, помеченный как deprecated до Qt 5.15
)

# Для Qt6 — корректное завершение настройки таргета
if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(SensorObserver)
endif()

# ---- Установка (опционально) ----
include(GNUInstallDirs)
install(TARGETS SensorObserver
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  BUNDLE  DESTINATION .
)
