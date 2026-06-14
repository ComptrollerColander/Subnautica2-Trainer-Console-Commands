#include "memory_rw.h"

bool ReadMemory(HANDLE hProcess, uintptr_t address, void* buffer, size_t size) {
    SIZE_T bytesRead;
    return ReadProcessMemory(hProcess, (LPCVOID)address, buffer, size, &bytesRead);
}

bool WriteMemory(HANDLE hProcess, uintptr_t address, void* buffer, size_t size) {
    SIZE_T bytesWritten;
    return WriteProcessMemory(hProcess, (LPVOID)address, buffer, size, &bytesWritten);
}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i) {
        ReadMemory(hProc, addr, &addr, sizeof(addr));
        addr += offsets[i];
    }
    return addr;
}