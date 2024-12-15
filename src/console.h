#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

#include "comands.h"
#include "defs.h"

class ConsoleParser {
public:
    ConsoleParser() = default;

    void RunParser();

private:
    word_t ReadArg();

private:
    std::unordered_map<std::string, std::shared_ptr<BaseComand>> comands_ = {
        {"run", std::make_shared<Run>()},
        {
            "stop",
            std::make_shared<Stop>(),
        },
        {"cont", std::make_shared<Cont>()},
        {"la", std::make_shared<La>()},
        {"ex", std::make_shared<Ex>()},
        {"dp", std::make_shared<Dp>()},
        {"sr", std::make_shared<Sr>()}};
};