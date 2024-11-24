#ifndef __PDP_H__
#define __PDP_H__

#include "../cpu/cpu.h"
#include "../mem/mem.h"

class PDP8I {
public:
public:
    Memory mem;

    struct {
        bool skip;
        bool pause;
        bool run;
        bool inte;
        bool irq;          // consider atomics
        bool dma;          // same
        bool three_cycle;  // same
    } flags;

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
    } regs;

    enum class MajState {
        Fetch,
        Defer,
        Execute,
        WordCount,
        CurAddr,
        Brk,
    } mstate;

private:
    void T1();

    void T2();

    void T3();

    void T4();

    void MemRead();

    void MemWr();

    void T2Execute();

    void T3Execute();

    void T3Fetch();

    void T4Fetch();

    void T4Defer();

    void T4Execute();

    void OPR();

    void IOT();
};

#endif