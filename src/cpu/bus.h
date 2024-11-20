#ifndef __BUS_H__
#define __BUS_H__

#include <atomic>

#include "../defs.h"

struct Bus {
    std::atomic<word_t> data;
    std::atomic<word_t> md;
};

#endif