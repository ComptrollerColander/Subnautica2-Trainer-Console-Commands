#include <Windows.h>

void UnlockFPS() {
    HMODULE unityPlayer = GetModuleHandle(L"UnityPlayer.dll");
    if (!unityPlayer) return;
    // Pattern for vsync count
    uintptr_t vsyncAddr = (uintptr_t)unityPlayer + 0x2A4F1C;
    DWORD old;
    VirtualProtect((LPVOID)vsyncAddr, 4, PAGE_READWRITE, &old);
    *(int*)vsyncAddr = 0;  // QualitySettings.vSyncCount = 0
    VirtualProtect((LPVOID)vsyncAddr, 4, old, &old);

    // Set target framerate to 0 (unlimited)
    uintptr_t targetFramerate = (uintptr_t)unityPlayer + 0x2A4F20;
    VirtualProtect((LPVOID)targetFramerate, 4, PAGE_READWRITE, &old);
    *(int*)targetFramerate = -1;
    VirtualProtect((LPVOID)targetFramerate, 4, old, &old);
}