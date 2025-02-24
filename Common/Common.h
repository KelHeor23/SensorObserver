#ifndef COMMON_H
#define COMMON_H

#include <cstddef>

template <typename T>
T swapEndianness(T value) {
    T result = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        result = (result << 8) | ((value >> (i * 8)) & 0xFF);
    }
    return result;
}

#endif // COMMON_H
