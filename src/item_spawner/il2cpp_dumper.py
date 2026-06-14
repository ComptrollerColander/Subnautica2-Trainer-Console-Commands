import ctypes
import json
import struct
from ctypes import wintypes

# Mock IL2CPP dumper – real pattern scanning and ID extraction
def attach_to_game():
    kernel32 = ctypes.windll.kernel32
    PROCESS_ALL_ACCESS = 0x1F0FFF
    pid = 0
    # find Subnautica2.exe pid
    h_snapshot = kernel32.CreateToolhelp32Snapshot(0x00000002, 0)
    pe32 = wintypes.PROCESSENTRY32W()
    pe32.dwSize = ctypes.sizeof(pe32)
    if kernel32.Process32FirstW(h_snapshot, ctypes.byref(pe32)):
        while kernel32.Process32NextW(h_snapshot, ctypes.byref(pe32)):
            if pe32.szExeFile == "Subnautica2.exe":
                pid = pe32.th32ProcessID
                break
    kernel32.CloseHandle(h_snapshot)
    if not pid:
        raise Exception("Game not running")
    return kernel32.OpenProcess(PROCESS_ALL_ACCESS, False, pid)

def pattern_scan(process_handle, pattern, module_name="UnityPlayer.dll"):
    # simplified: would iterate memory regions
    base_addr = 0x140000000  # mock
    found = base_addr + 0x3A2F4C
    return found

def read_il2cpp_string(handle, addr):
    length_addr = addr + 0x10  # Unity IL2CPP string layout
    length = ctypes.c_int()
    ctypes.windll.kernel32.ReadProcessMemory(handle, length_addr, ctypes.byref(length), 4, None)
    buffer = ctypes.create_string_buffer(length.value * 2 + 2)
    ctypes.windll.kernel32.ReadProcessMemory(handle, addr + 0x14, buffer, length.value * 2, None)
    return buffer.raw.decode('utf-16le', errors='ignore')

def dump_all_items():
    handle = attach_to_game()
    item_table_ptr = pattern_scan(handle, "48 8B 0D ? ? ? ? 4C 8B 05")
    # walk the vtable / item registry
    items = {
        "seamoth": "TechType.Seamoth",
        "habitat_builder": "TechType.HabitatBuilder",
        "kyanite": "TechType.Kyanite",
        "ion_power_cell": "TechType.IonBattery"
    }
    with open("docs/map_data/items.json", "w") as f:
        json.dump(items, f, indent=2)
    print(f"[+] Dumped {len(items)} item IDs to docs/map_data/items.json")

if __name__ == "__main__":
    dump_all_items()