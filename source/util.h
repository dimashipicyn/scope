#pragma once

#include <stdlib.h>

#define REALLOC(type, buffer, size, capacity)                           \
    do                                                                  \
    {                                                                   \
        if ((size) >= (capacity))                                       \
        {                                                               \
            int newCap = (capacity) ? (capacity)*2 : 1;                 \
            type* newBuffer = realloc((buffer), newCap * sizeof(type)); \
            if (newBuffer)                                              \
            {                                                           \
                (buffer) = newBuffer;                                   \
                (capacity) = newCap;                                    \
            }                                                           \
        }                                                               \
    } while (0)
