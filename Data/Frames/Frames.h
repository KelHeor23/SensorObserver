#ifndef FRAMES_H
#define FRAMES_H

#include <cstdint>
#include <memory>

enum FrameTypes{
    ESC_FRAME1,
    ESC_FRAME2,
    ESC_FRAME3,
    ENGINE,
    VOLTAGE_REGULATORS,
    OTHER_SENSROS,
    NONE
};

struct BaseFrame {
};

#pragma pack(push, 1) // Отключаем выравнивание
struct VoltageRegulatorsData : BaseFrame{
    uint32_t    canID;              // 0x1FF1210-0x1FF1217 (Младший бит - номер регулятора))
    uint8_t     inputVoltageHP;     // Входное напряжение (0-4095), старшая часть, вольт
    uint8_t     inputVoltageLP;     // Входное напряжение младшая часть, последние 4 бита - Входное напряжение (0-9), сотни мили-вольт
    uint8_t     electricCurrent;    // Ток (0 - 255), ампер
    uint16_t    controlPWM;         // Управляющий ШИМ, (0-2000), микро-секунды
    uint8_t     averageVoltageA;    // Среднее напряжение на фазе A (0-255), вольты/10
    uint8_t     averageVoltageB;    // Среднее напряжение на фазе B (0-255), вольты/10
    uint8_t     averageVoltageC;    // Среднее напряжение на фазе C (0-255), вольты/10
};
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания

#pragma pack(push, 1) // Отключаем выравнивание
struct EngineSensorsData : BaseFrame {
    uint32_t    canID;              // 0x1FF1200-0x1FF1207 (Младший бит - номер двигателя)
    uint16_t    speed;              // Обороты двигателя (0 - 65535), обор/м
    int8_t      temperature;        // Температура двигателя (-128 ... +127), градусы/10
    uint16_t    runoutAngle;        // Угол биения относительно метки на двигателе (0-359), градусы
    uint16_t    runoutAmplitude;    // Амплитуда биения (0 - 65535), мили-g
};
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания

#pragma pack(push, 1) // Отключаем выравнивание
struct OtherSensorsData : BaseFrame {
    uint32_t    canID;              // 0x1FF1200-0x1FF1207 (Младший бит - номер двигателя)
    double      reactiveTorquEngine1;   // Реактивный момент двигателя 1
    double      reactiveTorquEngine2;   // Реактивный момент двигателя 2
    double      thrustEngine1;          // тяга двигателя 1
    double      thrustEngine2;          // тяга двигателя 2
};
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания

namespace EscSensors {

struct EscStatusInfo1 : BaseFrame{
    int32_t     speed      = 0;      // 24-bit RPM motor speed (sign-extended to 32 bits)
    uint16_t    recv_pwm   = 0;  // 0.1us units (little-endian)
    uint16_t    comm_pwm   = 0;  // 0.1us units (little-endian)

    static std::shared_ptr<EscStatusInfo1> unpack(const char buffer[8]) {
        auto result = std::make_shared<EscStatusInfo1>();

        // Исправленный парсинг 24-битной скорости (little-endian)
        uint32_t raw_speed = static_cast<uint32_t>(static_cast<uint8_t>(buffer[2]) << 16) |
                             static_cast<uint32_t>(static_cast<uint8_t>(buffer[1]) << 8) |
                             static_cast<uint8_t>(buffer[0]);
        // Коррекция знака для 24-битного числа
        result->speed = (raw_speed & 0x800000) ?
                           (static_cast<int32_t>(raw_speed) | 0xFF000000) :
                           raw_speed;

        // Исправленный парсинг recv_pwm (little-endian)
        result->recv_pwm = static_cast<uint16_t>(static_cast<uint8_t>(buffer[4]) << 8) |
                          static_cast<uint16_t>(static_cast<uint8_t>(buffer[3]));

        // Исправленный парсинг comm_pwm (little-endian)
        result->comm_pwm = static_cast<uint16_t>(static_cast<uint8_t>(buffer[7]) << 8) |
                          static_cast<uint16_t>(static_cast<uint8_t>(buffer[6]));

        // Масштабирование PWM значений
        result->recv_pwm /= 10;
        result->comm_pwm /= 10;

        return result;
    }
};

#pragma pack(push, 1) // Отключаем выравнивание
struct EscStatusInfo2 : BaseFrame{
    uint16_t    voltage     = 0;    // 0.1V Bus voltage (little-endian)
    int16_t     bus_current = 0; // 0.1A Bus current (little-endian)
    int16_t     current     = 0;     // 0.1A Motor line current (little-endian)

    static std::shared_ptr<EscStatusInfo2> unpack(const char buffer[8]) {
        auto result = std::make_shared<EscStatusInfo2>();

        // Парсинг voltage (uint16_t, little-endian)
        result->voltage =
            (static_cast<uint16_t>(static_cast<uint8_t>(buffer[0])) |
             (static_cast<uint16_t>(static_cast<uint8_t>(buffer[1])) << 8)) / 10;

        // Парсинг bus_current (int16_t, little-endian)
        result->bus_current =
            static_cast<int16_t>(
                static_cast<uint16_t>(static_cast<uint8_t>(buffer[2])) |
                (static_cast<uint16_t>(static_cast<uint8_t>(buffer[3])) << 8)
                ) / 10;

        // Парсинг current (int16_t, little-endian)
        result->current =
            static_cast<int16_t>(
                static_cast<uint16_t>(static_cast<uint8_t>(buffer[4])) |
                (static_cast<uint16_t>(static_cast<uint8_t>(buffer[5])) << 8)
                ) / 10;

        return result;
    }
};
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания

#pragma pack(push, 1) // Отключаем выравнивание
struct EscStatusInfo3 : BaseFrame{
    uint8_t     cap_temp    = 0;        // Temperature in °C (беззнаковое)
    uint8_t     mcu_temp    = 0;        // Temperature in °C (беззнаковое)
    uint8_t     motor_temp  = 0;      // Temperature in °C (беззнаковое)
    uint16_t    Error       = 0;

    static std::shared_ptr<EscStatusInfo3> unpack(const char buffer[8]) {
        auto result = std::make_shared<EscStatusInfo3>();

        // Парсинг температур (прямое присваивание)
        result->cap_temp = static_cast<uint8_t>(buffer[2]) - 50;
        result->mcu_temp = static_cast<uint8_t>(buffer[3]) - 50;
        result->motor_temp = static_cast<uint8_t>(buffer[4]) - 50;

        // Парсинг резервных байт (buffer[5] и buffer[6]) или другой running_error
        result->Error =
            static_cast<uint16_t>(static_cast<uint8_t>(buffer[6])) |
            (static_cast<uint16_t>(static_cast<uint8_t>(buffer[7])) << 8);

        return result;
    }
};
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания
}

#endif // FRAMES_H
