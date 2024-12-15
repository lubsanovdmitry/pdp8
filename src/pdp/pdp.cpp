#include "pdp.h"

#include <stdexcept>

void PDP8I::MemWr() {
    mem.mem[memext.DF].data[regs.MA] = regs.MB;
}

void PDP8I::MemRead() {
    regs.MEM = mem.mem[memext.DF].data[regs.MA];
}

void PDP8I::T1() {
    switch (mstate) {
        case MajState::Fetch:
            regs.PC = EMU::incr(regs.MA);
            break;
        case MajState::Defer:
            break;
        case MajState::Execute:
            break;
        case MajState::WordCount:
            throw std::runtime_error{"Databreaks not supported"};
            break;
        case MajState::CurAddr:
            throw std::runtime_error{"Databreaks not supported"};
            break;
        case MajState::Brk:
            throw std::runtime_error{"Databreaks not supported"};
            break;
    }
}

void PDP8I::T2() {
    switch (mstate) {
        case MajState::Fetch:
            MemRead();
            regs.MB = regs.MEM;
            regs.IR = (regs.MEM & EMU::inst) >> 9;
            break;
        case MajState::Defer:
            MemRead();
            if (EMU::is_autoidx(regs.MA)) {
                regs.MB = EMU::incr(regs.MEM);
            } else {
                regs.MB = regs.MEM;
            }
            MemWr();
            break;
        case MajState::Execute:
            T2Execute();
            break;
        case MajState::WordCount:
            break;
        case MajState::CurAddr:
            break;
        case MajState::Brk:
            break;
    }
}

void PDP8I::T3() {
    switch (mstate) {
        case MajState::Fetch:
            T3Fetch();
            break;
        case MajState::Defer:
            if (regs.IR == static_cast<word_t>(EMU::Instr::JMP)) {
                if (EMU::is_autoidx(regs.MA)) {
                    regs.PC = EMU::incr(regs.MEM);
                } else {
                    regs.PC = regs.MEM;
                }
            }
            break;
        case MajState::Execute:
            break;
        case MajState::WordCount:
            break;
        case MajState::CurAddr:
            break;
        case MajState::Brk:
            break;
    }
}

void PDP8I::T4() {
    switch (mstate) {
        case MajState::Fetch:
            T4Fetch();
            break;
        case MajState::Defer:
            T4Defer();
            break;
        case MajState::Execute:
            T4Execute();
            break;
        case MajState::WordCount:
            break;
        case MajState::CurAddr:
            break;
        case MajState::Brk:
            break;
    }
}

void PDP8I::T2Execute() {
    MemRead();
    switch (static_cast<EMU::Instr>(regs.IR)) {
        case EMU::Instr::AND... EMU::Instr::TAD:
            regs.MB = regs.MEM;
            break;
        case EMU::Instr::ISZ:
            regs.MB = EMU::incr(regs.MEM);
            flags.skip = false;
            if (EMU::incr_l(regs.MEM) & EMU::link) {
                flags.skip = true;
            }
            break;
        case EMU::Instr::DCA:
            regs.MB = regs.AC;
            break;
        case EMU::Instr::JMS:
            if (flags.skip) {
                regs.MB = EMU::incr(regs.PC);
            } else {
                regs.MB = regs.PC;
            }
            break;
    }
    MemWr();
}

void PDP8I::T3Fetch() {
    switch (static_cast<EMU::Instr>(regs.IR)) {
        case EMU::Instr::JMP:
            if (!(regs.MB & 00400)) {
                regs.PC = regs.MEM & 00177;
                if (regs.MB & 00200) {
                    ;
                } else {
                    regs.PC |= regs.MA & 07600;
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

void PDP8I::T3Execute() {
    word_t res{};
    switch (static_cast<EMU::Instr>(regs.IR)) {
        case EMU::Instr::AND:
            regs.AC = regs.AC & regs.MB;
            break;
        case EMU::Instr::TAD:
            res = regs.AC + regs.MEM;
            regs.L = res & EMU::link;
            regs.AC = res & EMU::mask;
            break;
        case EMU::Instr::ISZ:
            break;
        case EMU::Instr::DCA:
            regs.AC = 0;
            break;
        case EMU::Instr::JMS:
            regs.PC = EMU::incr(regs.MA);
            break;
        default:
            std::logic_error{"Illegal opcode at this stage"};
            break;
    }
}

void PDP8I::T4Fetch() {
    switch (regs.IR) {
        case static_cast<int>(EMU::Instr::AND)... static_cast<int>(EMU::Instr::JMS):
            regs.MA = (regs.MEM & (M5 | M6 | M7 | M8 | M9 | M10 | M11)) |
                      ((regs.MB & M4) ? (regs.MA & (M0 | M1 | M2 | M3 | M4)) : 0);
            if (regs.MB & M3) {
                mstate = MajState::Defer;
            } else {
                mstate = MajState::Execute;
            }
            break;
        default:
            if (flags.irq) {
                regs.MA = 0;
                regs.IR = static_cast<int>(EMU::Instr::JMS);
                mstate = MajState::Execute;
            } else if (flags.dma) {
                33a;
                if (flags.three_cycle) {
                    mstate = MajState::WordCount;
                } else {
                    mstate = MajState::Brk;
                }
            } else {
                if (flags.skip) {
                    flags.skip = 0;
                    regs.MA = EMU::incr(regs.PC);
                } else {
                    regs.MA = regs.PC;
                }
                mstate = MajState::Fetch;
            }
    }
}

void PDP8I::T4Defer() {
    if (regs.IR == static_cast<word_t>(EMU::Instr::JMP)) {
        if (flags.dma) {
            throw std::runtime_error{"Databreaks not implemented"};
        } else if (flags.irq) {
            regs.MA = 0;
            regs.IR = static_cast<word_t>(EMU::Instr::JMS);
            mstate = MajState::Execute;
        } else {
            regs.MA = regs.PC;
            mstate = MajState::Execute;
        }
    } else {
        if (EMU::is_autoidx(regs.MA)) {
            regs.MA = EMU::incr(regs.MEM);
        } else {
            regs.MA = regs.MEM;
        }
    }
}

void PDP8I::T4Execute() {
    if (flags.irq) {
        regs.MA = 0;
        regs.IR = EMU::Instr::JMS;
        mstate = MajState::Execute;
    } else if (flags.dma) {
        throw std::runtime_error{"Databreak not implemented"};
    } else {
        if (flags.skip) {
            regs.MA = EMU::incr(regs.PC);
        } else {
            regs.MA = regs.PC;
        }
        mstate = MajState::Fetch;
    }
}

void PDP8I::IOT() {
}

void PDP8I::OPR() {
    if (regs.MB & M3) {
        flags.skip = false;
        if (((regs.MB & M6) && !(regs.AC & EMU::mask)) ||
            ((regs.MB & M5) && ((regs.AC & EMU::mask) & M0)) ||
            ((regs.MB & M7) && !(regs.AC & EMU::link))) {
            flags.skip = true;
        }
        if ((regs.MB & M8)) {
            flags.skip = !flags.skip;
        }
        if ((regs.MB & M10) && !(regs.MB & M11)) {
            flags.run = false;
        }
        if (regs.MB & M5) {
            regs.AC &= EMU::link;
        }
        if (regs.MB & M9) {
            regs.AC |= regs.SR;
        }
    } else {
        if (regs.MB & M4) {
            regs.AC &= EMU::link;
        }
        if (regs.MB & M6) {
            regs.AC &= EMU::link;
            regs.AC |= (~regs.AC) & EMU::mask;
        }
        if (regs.MB & M5) {
            regs.L = 0;
        }
        if (regs.MB & M7) {
            regs.L = !regs.L;
        }
        if (regs.MB & M8) {
            {
                bool low = regs.AC & M11;
                regs.AC >>= 1;
                regs.AC &= EMU::mask;
                regs.AC |= (regs.L) ? M0 : 0;
                regs.L = low;
            }
            if (regs.MB & M10) {
                bool low = regs.AC & M11;
                regs.AC >>= 1;
                regs.AC &= EMU::mask;
                regs.AC |= (regs.L) ? M0 : 0;
                regs.L = low;
            }
        }
        if (regs.MB & M9) {
            {
                regs.AC <<= 1;
                regs.AC |= (regs.L) ? 1 : 0;
                regs.L = regs.AC & EMU::link;
                regs.AC &= EMU::mask;
            }
            if (regs.MB & M10) {
                regs.AC <<= 1;
                regs.AC |= (regs.L) ? 1 : 0;
                regs.L = regs.AC & EMU::link;
                regs.AC &= EMU::mask;
            }
        }
        if (regs.MB & M11) {
            regs.AC = EMU::incr(regs.AC);
        }
    }
}
