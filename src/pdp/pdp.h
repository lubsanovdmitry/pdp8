#ifndef __PDP_H__
#define __PDP_H__

#include <atomic>

#include "../mem/mem.h"

class PDP8I {
public:
public:
    Memory mem;

    struct {
        bool skip;
        bool pause;
        std::atomic<bool> run;
        bool inte;
        bool irq;          // consider atomics
        bool dma;          // same
        bool three_cycle;  // same
    } flags;

    struct {
        word_t IF;
        word_t DF;
        word_t IB;
        word_t SF;
        word_t BF;
    } memext;
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

    void T1();

    void T2();

    void T3();

    void T4();

    void Run() {
        while (true) {
            while (flags.run.load() == false) {
                flags.run.wait(false);
            }
            SingleStep();
        }
    }

    void SingleStep() {
        T1();
        T2();
        T3();
        T4();
    }

    void LA() {
        regs.PC = regs.SR;
    }

    void EX() {
        regs.MA = regs.PC;
        regs.PC = EMU::incr(regs.PC);
        MemRead();
    }

    void DP() {
        regs.MA = regs.PC;
        regs.PC = EMU::incr(regs.PC);
        regs.MB = regs.SR;
        MemWr();
    }

private:
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