#ifndef __CPU8E_H__
#define __CPU8E_H__

#include "../defs.h"

/// KK8E

///
struct Regs {
    word_t AC;
    word_t PC;
    word_t MQ;
    word_t CPMA;
    word_t MB;
};

struct CPU {};

#endif