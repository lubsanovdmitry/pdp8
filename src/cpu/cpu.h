#ifndef __CPU_H__
#define __CPU_H__

#include "../defs.h"

struct Regs {
    word_t AC;
    word_t PC;
    word_t MQ;
};

struct CPU {};

#endif