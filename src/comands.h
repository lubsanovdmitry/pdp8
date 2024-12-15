#pragma once

#include <functional>

#include "defs.h"
#include "emu.h"

struct BaseComand {
    BaseComand(bool flag) : req_args(flag) {
    }
    virtual void Launch() = 0;
    bool req_args;
    word_t arg;
};

struct Run : BaseComand {
    Run() : BaseComand(false) {
    }
    void Launch() override;
};

struct Stop : BaseComand {
    Stop() : BaseComand(false) {
    }
    void Launch() override;
};

struct Cont : BaseComand {
    Cont() : BaseComand(false) {
    }
    void Launch() override;
};

struct La : BaseComand {
    La() : BaseComand(true) {
    }
    void Launch() override;
};

struct Ex : BaseComand {
    Ex() : BaseComand(false) {
    }
    void Launch() override;
};

struct Dp : BaseComand {
    Dp() : BaseComand(true) {
    }
    void Launch() override;
};

struct Sr : BaseComand {
    Sr() : BaseComand(true) {
    }
    void Launch() override;
};

struct PrRegs : BaseComand {
    PrRegs() : BaseComand(false) {
    }
    void Launch() override;
};
