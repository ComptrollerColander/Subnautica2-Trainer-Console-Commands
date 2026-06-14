#include <iostream>
#include "../src/memory_core/pattern_scanner.cpp"

int main() {
    uintptr_t addr = PatternScan("UnityPlayer.dll", "48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 89 45");
    if (addr)
        std::cout << "Pattern found at: 0x" << std::hex << addr << std::endl;
    else
        std::cout << "Pattern not found (game not running or module not loaded)." << std::endl;
    return 0;
}