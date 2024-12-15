#ifndef __EMU_H__
#define __EMU_H__

#include <condition_variable>
#include <thread>

#include "defs.h"
#include "pdp/pdp.h"

class Emulator {
public:
    Emulator() : pdp8_{}, t_{} {
        t_ = std::move(std::jthread(&PDP8I::Run, &pdp8_));
    }

    void Run() {
        pdp8_.flags.inte = 0;
        pdp8_.mstate = PDP8I::MajState::Fetch;
        pdp8_.regs.AC = 0;
        pdp8_.regs.L = 0;
        pdp8_.flags.run.store(true);
        pdp8_.flags.run.notify_one();
    }

    void Cont() {
        pdp8_.flags.run.store(true);
        pdp8_.flags.run.notify_one();
    }

    void Stop() {
        pdp8_.flags.run.store(false);
    }

    void SingleCycle() {
        pdp8_.SingleStep();
    }

    void LA() {
        pdp8_.LA();
    }

    void EX() {
        pdp8_.EX();
    }

    void DP() {
        pdp8_.DP();
    }

    void SR(word_t w) {
        pdp8_.regs.SR = w;
    }

    void PrRegs() {
        pdp8_.PrRegs();
    }

private:
    PDP8I pdp8_;
    std::jthread t_;
};

#endif