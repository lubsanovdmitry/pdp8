#ifndef __CPU8_H__
#define __CPU8_H__

#include "../defs.h"
#include "../mem/mem.h"

/// KK8E

///

struct CPU {
    enum class MajState {
        Fetch,
        Defer,
        Execute,
        WordCount,
        CurAddr,
        Brk,
    };

    struct Regs {
        bool L;
        word_t AC;
        word_t PC;
        word_t MA;
        word_t MB;
        word_t IR;
        word_t SR;
        word_t MQ;
        word_t MEM;
    };

    MajState mstate;

    Regs regs;
};

#endif