#pragma once
#include <Windows.h>
#include <cstdint>

bool ReadMemory(HANDLE hProcess, uintptr_t address, void* buffer, size_t size);
bool WriteMemory(HANDLE hProcess, uintptr_t address, void* buffer, size_t size);
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);