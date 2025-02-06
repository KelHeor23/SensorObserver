#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent},
    engineSensors(new EngineSensors),
    hBoxLayout(new QHBoxLayout(this)),
    listOfLimits(new ListOfLimits(*engineSensors, this)),
    sensorsEngine_1(new DisplayingSensors(this)),
    sensorsEngine_2(new DisplayingSensors(this)),
    sensorsEngine_3(new DisplayingSensors(this)),
    sensorsEngine_4(new DisplayingSensors(this)),
    client(new Client(this))
{
    QWidget *centralWidget = new QWidget((this)); // Создаем центральный виджет
    setCentralWidget(centralWidget); // Устанавливаем центральный виджет

    centralWidget->setLayout(hBoxLayout); // Применяем компоновку к центральному виджету

    hBoxLayout->addWidget(listOfLimits);
    hBoxLayout->addWidget(sensorsEngine_1);
    hBoxLayout->addWidget(sensorsEngine_2);
    hBoxLayout->addWidget(sensorsEngine_3);
    hBoxLayout->addWidget(sensorsEngine_4);
}

void MainWindow::fillSensorsEngines()
{
    struct EngineSensorsData {
        uint32_t    canID;
        uint16_t    speed;            // Обороты двигателя (0 - 65535), обор/м
        int8_t      temperature;        // Температура двигателя (-128 ... +127), градусы/10
        uint16_t    runoutAngle;        // Угол биения относительно метки на двигателе (0-359), градусы
        uint16_t    runoutAmplitude;    // Амплитуда биения (0 - 65535), мили-g
    };

    EngineSensorsData data;

    data.canID = rand() % 1000000000 + 1;
    data.speed = rand() % (65536);
    data.temperature = static_cast<int8_t>(rand() % (256) - 128);
    data.runoutAngle = rand() % (360);
    data.runoutAmplitude = rand() % (65536);

    std::string str(reinterpret_cast<char *> (&data), sizeof(data));

    sensorsEngine_1->setEngineSensorsData(str);

    data.canID = rand() % 1000000000 + 1;
    data.speed = rand() % (65536);
    data.temperature = static_cast<int8_t>(rand() % (256) - 128);
    data.runoutAngle = rand() % (360);
    data.runoutAmplitude = rand() % (65536);

    str = std::string(reinterpret_cast<char *> (&data), sizeof(data));

    sensorsEngine_2->setEngineSensorsData(str);

    data.canID = rand() % 1000000000 + 1;
    data.speed = rand() % (65536);
    data.temperature = static_cast<int8_t>(rand() % (256) - 128);
    data.runoutAngle = rand() % (360);
    data.runoutAmplitude = rand() % (65536);

    str = std::string(reinterpret_cast<char *> (&data), sizeof(data));

    sensorsEngine_3->setEngineSensorsData(str);

    data.canID = rand() % 1000000000 + 1;
    data.speed = rand() % (65536);
    data.temperature = static_cast<int8_t>(rand() % (256) - 128);
    data.runoutAngle = rand() % (360);
    data.runoutAmplitude = rand() % (65536);

    str = std::string(reinterpret_cast<char *> (&data), sizeof(data));

    sensorsEngine_4->setEngineSensorsData(str);
}
