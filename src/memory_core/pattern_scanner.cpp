#include <Windows.h>
#include <vector>
#include <cstdint>

uintptr_t PatternScan(const char* moduleName, const char* pattern) {
    HMODULE module = GetModuleHandleA(moduleName);
    if (!module) return 0;

    MODULEINFO modInfo = { 0 };
    GetModuleInformation(GetCurrentProcess(), module, &modInfo, sizeof(modInfo));
    uintptr_t start = (uintptr_t)module;
    uintptr_t end = start + modInfo.SizeOfImage;

    // Convert pattern string to bytes + mask
    std::vector<int> bytes;
    std::string mask;
    const char* p = pattern;
    while (*p) {
        if (*p == ' ') { p++; continue; }
        if (*p == '?') {
            bytes.push_back(-1);
            mask += '?';
            p++;
            if (*p == '?') p++;
            if (*p == ' ') p++;
        } else {
            char hex[3] = { p[0], p[1], 0 };
            bytes.push_back(strtol(hex, nullptr, 16));
            mask += 'x';
            p += 2;
        }
    }

    for (uintptr_t i = start; i < end - bytes.size(); i++) {
        bool found = true;
        for (size_t j = 0; j < bytes.size(); j++) {
            if (mask[j] == 'x' && *(BYTE*)(i + j) != bytes[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return 0;
}