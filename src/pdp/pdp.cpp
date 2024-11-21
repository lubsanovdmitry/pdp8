#include "pdp.h"

void PDP8I::T1() {
    switch (cpu_.mstate) {
        case CPU::MajState::Fetch:
            cpu_.regs.PC = EMU::incr(cpu_.regs.MA);
            MemRead();
            break;
        case CPU::MajState::Defer:
            break;
        case CPU::MajState::Execute:
            break;
        case CPU::MajState::WordCount:
            break;
        case CPU::MajState::CurAddr:
            break;
        case CPU::MajState::Brk:
            break;
    }
}

void PDP8I::T2() {
    switch (cpu_.mstate) {
        case CPU::MajState::Fetch:
            cpu_.regs.MB = cpu_.regs.MEM;
            cpu_.regs.IR = (cpu_.regs.MEM & EMU::inst) >> 9;
            MemWr();
            break;
        case CPU::MajState::Defer:
            if (EMU::is_autoidx(cpu_.regs.MA)) {
                cpu_.regs.MB = EMU::incr(cpu_.regs.MEM);
            } else {
                cpu_.regs.MB = cpu_.regs.MEM;
            }
            MemWr();
            break;
        case CPU::MajState::Execute:
            break;
        case CPU::MajState::WordCount:
            break;
        case CPU::MajState::CurAddr:
            break;
        case CPU::MajState::Brk:
            break;
    }
}

void PDP8I::T3() {
    switch (cpu_.mstate) {
        case CPU::MajState::Fetch:
            DecodeT3();
            break;
        case CPU::MajState::Defer:

            break;
        case CPU::MajState::Execute:
            break;
        case CPU::MajState::WordCount:
            break;
        case CPU::MajState::CurAddr:
            break;
        case CPU::MajState::Brk:
            break;
    }
}

void PDP8I::T4() {
    switch (cpu_.mstate) {
        case CPU::MajState::Fetch:

            break;
        case CPU::MajState::Defer:

            break;
        case CPU::MajState::Execute:
            break;
        case CPU::MajState::WordCount:
            break;
        case CPU::MajState::CurAddr:
            break;
        case CPU::MajState::Brk:
            break;
    }
}

void PDP8I::DecodeT3() {
    switch (static_cast<EMU::Instr>(cpu_.regs.IR)) {
        case EMU::Instr::JMP:
            if (!(cpu_.regs.MB & 00400)) {
                cpu_.regs.PC = cpu_.regs.MEM & 00177;
                if (cpu_.regs.MB & 00200) {
                    ;
                } else {
                    cpu_.regs.PC |= cpu_.regs.MA & 07600;
                }
            }
            break;
        case EMU::Instr::IOT:
            IOT();
            break;
        case EMU::Instr::OPR:
            OPR();
            break;
        default:
            break;
    }
}

void PDP8I::IOT() {
}  // namespace

void PDP8I::OPR() {
    if (cpu_.regs.MB & M3) {
        if (((cpu_.regs.MB & M6) && !(cpu_.regs.AC & EMU::mask)) ||
            ((cpu_.regs.MB & M5) && ((cpu_.regs.AC & EMU::mask) & M0)) ||
            ((cpu_.regs.MB & M7) && !(cpu_.regs.AC & EMU::link))) {
            flags.skip = true;
        }
        if ((cpu_.regs.MB & M8)) {
            flags.skip = !flags.skip;
        }
        if ((cpu_.regs.MB & 00002) && !(cpu_.regs.MB & 00001)) {
            flags.run = false;
        }
        if (cpu_.regs.MB & 00100) {
            cpu_.regs.AC &= EMU::link;
        }
        if (cpu_.regs.MB & 00004) {
            cpu_.regs.AC |= cpu_.regs.SR;
        }
    } else {
        if (cpu_.regs.MB & M4) {
            cpu_.regs.AC &= EMU::link;
        }
        if (cpu_.regs.MB & M6) {
            cpu_.regs.AC &= EMU::link;
            cpu_.regs.AC |= (~cpu_.regs.AC) & EMU::mask;
        }
        if (cpu_.regs.MB & M5) {
            cpu_.regs.L = 0;
        }
        if (cpu_.regs.MB & M7) {
            cpu_.regs.L = !cpu_.regs.L;
        }
        if (cpu_.regs.MB & M8) {
            {
                bool low = cpu_.regs.AC & M11;
                cpu_.regs.AC >>= 1;
                cpu_.regs.AC &= EMU::mask;
                cpu_.regs.AC |= (cpu_.regs.L) ? 04000 : 0;
                cpu_.regs.L = low;
            }
            if (cpu_.regs.MB & M10) {
                bool low = cpu_.regs.AC & M11;
                cpu_.regs.AC >>= 1;
                cpu_.regs.AC &= EMU::mask;
                cpu_.regs.AC |= (cpu_.regs.L) ? 04000 : 0;
                cpu_.regs.L = low;
            }
        }
        if (cpu_.regs.MB & M9) {
            {
                cpu_.regs.AC <<= 1;
                cpu_.regs.AC |= (cpu_.regs.L) ? 1 : 0;
                cpu_.regs.L = cpu_.regs.AC & EMU::link;
                cpu_.regs.AC &= EMU::mask;
            }
            if (cpu_.regs.MB & M10) {
                cpu_.regs.AC <<= 1;
                cpu_.regs.AC |= (cpu_.regs.L) ? 1 : 0;
                cpu_.regs.L = cpu_.regs.AC & EMU::link;
                cpu_.regs.AC &= EMU::mask;
            }
        }
        if (cpu_.regs.MB & M11) {
            cpu_.regs.AC = EMU::incr(cpu_.regs.AC);
        }
    }
}
