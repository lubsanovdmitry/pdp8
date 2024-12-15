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
}

void Dp::Launch() {
    emu.SR(arg);
    emu.DP();
}

void Sr::Launch() {
    emu.SR(arg);
}