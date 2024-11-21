#ifndef __MEM_H__
#define __MEM_H__

#include <array>
#include <cstddef>

#include "../defs.h"

struct Memory {
    struct MemBank {
        static constexpr size_t BANKSIZE = 4096;
        std::array<word_t, BANKSIZE> data;
    };

    std::array<MemBank, 8> mem;
};

#endif