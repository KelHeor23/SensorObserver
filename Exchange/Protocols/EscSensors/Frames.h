#ifndef FRAMES_H
#define FRAMES_H

#include <cstdint>

namespace EscSensors {

struct EscStatusInfo1{
    bool isCustomSensros    = 0;    // Флаг о том, что данные пришли с не вшшитых датчиков в ESc
    int32_t  speed          = 0;    // 24-bit RPM motor speed (sign-extended to 32 bits)
    uint16_t recv_pwm       = 0;    // 0.1us units (little-endian)
    uint16_t comm_pwm       = 0;    // 0.1us units (little-endian)

    static EscStatusInfo1 unpack(const char buffer[8]) {
    EscStatusInfo1 result;

    // Исправленный парсинг 24-битной скорости (little-endian)
    uint32_t raw_speed = static_cast<uint32_t>(static_cast<uint8_t>(buffer[2]) << 16) |
                         static_cast<uint32_t>(static_cast<uint8_t>(buffer[1]) << 8) |
                         static_cast<uint8_t>(buffer[0]);
    // Коррекция знака для 24-битного числа
    result.speed = (raw_speed & 0x800000) ?
                   (static_cast<int32_t>(raw_speed) | 0xFF000000) :
                   raw_speed;

    // Исправленный парсинг recv_pwm (little-endian)
    result.recv_pwm = static_cast<uint16_t>(static_cast<uint8_t>(buffer[4]) << 8) |
                      static_cast<uint16_t>(static_cast<uint8_t>(buffer[3]));

    // Исправленный парсинг comm_pwm (little-endian)
    result.comm_pwm = static_cast<uint16_t>(static_cast<uint8_t>(buffer[7]) << 8) |
                      static_cast<uint16_t>(static_cast<uint8_t>(buffer[6]));

    // Масштабирование PWM значений
    result.recv_pwm /= 10;
    result.comm_pwm /= 10;

    return result;
    }
};

#pragma pack(push, 1) // Отключаем выравнивание
struct EscStatusInfo2{
    bool isCustomSensros    = 0;    // Флаг о том, что данные пришли с не вшшитых датчиков в ESc
    uint16_t voltage        = 0;    // 0.1V Bus voltage (little-endian)
    int16_t bus_current     = 0;    // 0.1A Bus current (little-endian)
    int16_t current         = 0;    // 0.1A Motor line current (little-endian)

    static EscStatusInfo2 unpack(const char buffer[8]) {
        EscStatusInfo2 result;

        // Парсинг voltage (uint16_t, little-endian)
        result.voltage =
            (static_cast<uint16_t>(static_cast<uint8_t>(buffer[0])) |
            (static_cast<uint16_t>(static_cast<uint8_t>(buffer[1])) << 8)) / 10;

        // Парсинг bus_current (int16_t, little-endian)
        result.bus_current =
            static_cast<int16_t>(
                static_cast<uint16_t>(static_cast<uint8_t>(buffer[2])) |
                (static_cast<uint16_t>(static_cast<uint8_t>(buffer[3])) << 8)
                ) / 10;

        // Парсинг current (int16_t, little-endian)
        result.current =
            static_cast<int16_t>(
                static_cast<uint16_t>(static_cast<uint8_t>(buffer[4])) |
                (static_cast<uint16_t>(static_cast<uint8_t>(buffer[5])) << 8)
                ) / 10;

        return result;
    }
};
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания

#pragma pack(push, 1) // Отключаем выравнивание
struct EscStatusInfo3{
    bool isCustomSensros    = 0;    // Флаг о том, что данные пришли с не вшшитых датчиков в ESc
    uint8_t cap_temp        = 0;    // Temperature in °C (беззнаковое)
    uint8_t mcu_temp        = 0;    // Temperature in °C (беззнаковое)
    uint8_t motor_temp      = 0;    // Temperature in °C (беззнаковое)
    uint16_t Error;

    static EscStatusInfo3 unpack(const char buffer[8]) {
        EscStatusInfo3 result;

        // Парсинг температур (прямое присваивание)
        result.cap_temp = static_cast<uint8_t>(buffer[2]) - 50;
        result.mcu_temp = static_cast<uint8_t>(buffer[3]) - 50;
        result.motor_temp = static_cast<uint8_t>(buffer[4]) - 50;

        // Парсинг резервных байт (buffer[5] и buffer[6]) или другой running_error
        result.Error =
            static_cast<uint16_t>(static_cast<uint8_t>(buffer[6])) |
            (static_cast<uint16_t>(static_cast<uint8_t>(buffer[7])) << 8);

        return result;
    }
};
#pragma pack(pop) // Восстанавливаем предыдущее значение выравнивания
}
#endif // FRAMES_H
