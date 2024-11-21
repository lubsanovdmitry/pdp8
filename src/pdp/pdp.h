#ifndef __PDP_H__
#define __PDP_H__

#include "../cpu/cpu.h"
#include "../mem/mem.h"

class PDP8I {
public:
private:
    CPU cpu_;
    Memory mem_;

    struct {
        bool skip;
        bool pause;
        bool run;
    } flags;

private:
    void T1();

    void T2();

    void T3();

    void T4();

    void MemRead();

    void MemWr();

    void DecodeT3();

    void OPR();

    void IOT();
};

#endif