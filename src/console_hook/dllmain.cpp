#include <Windows.h>
#include <MinHook.h>

typedef bool (*IsConsoleAllowedFn)();
IsConsoleAllowedFn original_IsConsoleAllowed = nullptr;

bool Hooked_IsConsoleAllowed() {
    return true;
}

DWORD WINAPI MainThread(LPVOID lpParam) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    printf("[+] Subnautica 2 DevTools injected\n");

    HMODULE gameAsm = GetModuleHandle(L"GameAssembly.dll");
    uintptr_t flagAddr = (uintptr_t)gameAsm + 0x3F2A8C;
    BYTE* flagByte = reinterpret_cast<BYTE*>(flagAddr);
    *flagByte = 0x01;

    MH_Initialize();
    MH_CreateHook((LPVOID)((uintptr_t)gameAsm + 0x123456), &Hooked_IsConsoleAllowed, (LPVOID*)&original_IsConsoleAllowed);
    MH_EnableHook(MH_ALL_HOOKS);

    uintptr_t vsyncAddr = (uintptr_t)GetModuleHandle(L"UnityPlayer.dll") + 0x2A4F1C;
    DWORD oldProtect;
    VirtualProtect((LPVOID)vsyncAddr, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
    *(BYTE*)vsyncAddr = 0x00;
    VirtualProtect((LPVOID)vsyncAddr, 1, oldProtect, &oldProtect);

    printf("[+] Console unlocked, VSync disabled (FPS cap removed)\n");

    while (true) {
        if (GetAsyncKeyState(VK_F2) & 1) {
            uintptr_t healthAddr = (uintptr_t)gameAsm + 0x1F4A8C0;
            float maxHealth = 9999.0f;
            WriteProcessMemory(GetCurrentProcess(), (LPVOID)healthAddr, &maxHealth, 4, NULL);
            printf("[*] God mode toggled\n");
        }
        Sleep(100);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
    return TRUE;
}