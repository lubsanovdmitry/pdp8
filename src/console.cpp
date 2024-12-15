#include "console.h"
#include <stdexcept>

const std::string EXIT_TOKEN = "ex";

void ConsoleParser::RunParser() {
    while (true) {
        std::cout << "Enter comand:\n";
        std::string token;
        word_t arg;
        std::cin >> token;
        if (comands_.find(token) == comands_.end()) {
            throw std::runtime_error("There is no such comand");
        }
        if (comands_[token]->req_args) {
            arg = ReadArg();
            comands_[token]->arg = arg;
        }
        comands_[token]->Launch();
        if (token == EXIT_TOKEN) {
            std::cout << "---Exited from PDP8 emulator---";
            return;
        }
    }
}

word_t ConsoleParser::ReadArg() {
    word_t arg;
    std::cin >> arg;
    return arg;
}