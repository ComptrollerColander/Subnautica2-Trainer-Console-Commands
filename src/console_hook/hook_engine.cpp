#include "hook_engine.h"
#include <iostream>

void EnableDeveloperConsole() {
    HMODULE gameAssembly = GetModuleHandle(L"GameAssembly.dll");
    if (!gameAssembly) return;
    uintptr_t consoleFlag = (uintptr_t)gameAssembly + 0x4A2F1C;
    DWORD old;
    VirtualProtect((LPVOID)consoleFlag, 1, PAGE_READWRITE, &old);
    *(bool*)consoleFlag = true;
    VirtualProtect((LPVOID)consoleFlag, 1, old, &old);
    std::cout << "[HOOK] Developer console enabled.\n";
}