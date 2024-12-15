#include "comands.h"

Emulator emu;

void Run::Launch() {
    emu.Run();
}

void Stop::Launch() {
    emu.Stop();
}

void Cont::Launch() {
    emu.Cont();
}

void La::Launch() {
    emu.SR(arg);
    emu.LA();
}

void Ex::Launch() {
    emu.EX();
    emu.PrRegs();
}

void Dp::Launch() {
    emu.SR(arg);
    emu.DP();
}

void Sr::Launch() {
    emu.SR(arg);
}

void PrRegs::Launch() {
    emu.PrRegs();
}