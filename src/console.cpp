#include "console.h"

#include <stdexcept>

constexpr std::string EXIT_TOKEN = "exit";

void ConsoleParser::RunParser() {
    while (true) {
        std::cout << "Enter comand:\n";
        std::string token;
        word_t arg;
        std::cin >> token;
        if (token == EXIT_TOKEN) {

            std::cout << "---Exited from PDP8 emulator---\n";
            return;
        }
        if (commands_.find(token) == commands_.end()) {
            std::cout << "There is no such comand" << std::endl;
            continue;
        }
        if (commands_[token]->req_args) {
            arg = ReadArg();
            commands_[token]->arg = arg;
        }
        commands_[token]->Launch();
    }
}

word_t ConsoleParser::ReadArg() {
    word_t arg;
    std::cin >> arg;
    return arg;
}