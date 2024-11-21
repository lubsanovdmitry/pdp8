#ifndef __DEFS_H__
#define __DEFS_H__

#include <cstdint>

using word_t = uint16_t;

namespace EMU {
constexpr uint16_t mask = 07777;
constexpr uint16_t link = 010000;
constexpr uint16_t inst = 07000;

constexpr word_t incr(word_t i) {
    ++i;
    return i & EMU::mask;
}

constexpr word_t incr_l(word_t i) {
    ++i;
    return i & (EMU::mask | EMU::link);
}

constexpr bool is_autoidx(word_t i) {
    switch (i) {
        case 010 ... 017:
            return true;
        default:
            return false;
    }
}

enum class Instr : int {
    AND = 0,
    TAD,
    ISZ,
    DCA,
    JMS,
    JMP,
    IOT,
    OPR,
};
}  // namespace EMU

constexpr word_t M0 = 04000;
constexpr word_t M1 = 02000;
constexpr word_t M2 = 01000;
constexpr word_t M3 = 00400;
constexpr word_t M4 = 00200;
constexpr word_t M5 = 00100;
constexpr word_t M6 = 00040;
constexpr word_t M7 = 00020;
constexpr word_t M8 = 00010;
constexpr word_t M9 = 00004;
constexpr word_t M10 = 00002;
constexpr word_t M11 = 00001;

#endif
