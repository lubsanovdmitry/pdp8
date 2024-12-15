#include "console.h"
#include "emu.h"
#include "pdp/pdp.h"

int main() {
    std::cin >> std::oct;
    ConsoleParser CP;
    CP.RunParser();
    return 0;
}