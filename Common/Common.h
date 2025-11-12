/**
 * \file Common.h
 * \brief Общие утилиты проекта, функции низкого уровня.
 * \date 2025-11-07
 *
 * This file is part of the SensorObserver project.
 */
#ifndef COMMON_H
#define COMMON_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <type_traits>
#endif

/**
 * \brief Меняет порядок байт (эндивность) значения любого тривиального целочисленного типа.
 * \tparam T Целочисленный тип (например, uint16_t, uint32_t, uint64_t).
 * \param value Входное значение в исходной эндивности.
 * \return Значение с обратным порядком байт.
 * \warning Шаблон рассчитан на целочисленные типы и не предназначен для float/double.
 */
template <typename T>
T swapEndianness(T value) {
    static_assert(std::is_integral_v<T> || std::is_enum_v<T>, "swapEndianness expects integral type");
    T result{};
    auto* in  = reinterpret_cast<unsigned char*>(&value);
    auto* out = reinterpret_cast<unsigned char*>(&result);
    for (std::size_t i = 0; i < sizeof(T); ++i) {
        out[i] = in[sizeof(T)-1-i];
    }
    return result;
}

#endif // COMMON_H
