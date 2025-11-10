/**
 * \file main.cpp
 * \brief Точка входа в приложение Qt (SensorObserver).
 * \date 2025-11-07
 *
 * This file is part of the SensorObserver project.

 */


#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <QtWidgets/QApplication>
#endif

#include "Widgets/MainWindow.h"

/// \brief Точка входа Qt-приложения.
/// \param argc Количество аргументов командной строки.
/// \param argv Массив аргументов.
/// \return Код возврата Qt event loop.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;

    mainWindow.showMaximized();

    return a.exec();
}
