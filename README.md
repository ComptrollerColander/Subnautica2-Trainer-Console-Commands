<div align="center">

![Header Banner](https://capsule-render.vercel.app/api?type=waving&color=0b2b40&height=200&section=header&text=Subnautica%202%20DevTools&fontSize=50&fontColor=00ffcc&desc=Console%20%7C%20Trainer%20%7C%20Memory%20API%20%7C%20Item%20Spawner&descAlignY=70)

![Downloads](https://img.shields.io/badge/Downloads-284-success?style=for-the-badge&color=0b2b40)
[![Release](https://img.shields.io/github/v/release/ComptrollerColander/Subnautica2-Trainer-Console-Commands?style=for-the-badge&color=00ffcc)](../../releases)
[![Status](https://img.shields.io/badge/Status-Undetected%20%2F%20Safe-success?style=for-the-badge)]()
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Steam-informational?style=for-the-badge)]()
[![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)](LICENSE)

**Open‑source IL2CPP memory wrapper + developer console enabler for Subnautica 2**  
*Single‑player research & modding framework*

</div>

---

> 🧪 **EDUCATIONAL DISCLAIMER**  
> This project is a **proof‑of‑concept** for memory research, offline debugging, and mod development.  
> It does **not** bypass DRM, interact with multiplayer servers, or modify permanent game files.  
> Use only on your own single‑player saves. The authors assume no liability for corrupted data.

---

## 🔥 Why This Exists

Subnautica 2 is beautiful, but sometimes you just want to:
- **Skip the grind** and focus on base building
- **Test every item** without hunting for blueprints
- **Explore freely** without oxygen or hunger limits
- **Enable the hidden developer console** for fun commands

This tool gives you **safe, runtime‑only** memory manipulation – nothing is permanently changed.

---

## ⚡ Features & Hotkeys

| Module | Technical Backend | User Benefit | Hotkey |
|--------|------------------|--------------|--------|
| **Developer Console** | Patches `UI_DeveloperConsole.IsAllowed` in memory | Press `~` to open dev console | `F1` |
| **God Mode (Vitals Lock)** | Freezes `PlayerVitals` struct (health/oxygen/energy) | Infinite health, unlimited oxygen, no hunger | `F2` |
| **IL2CPP Item Spawner** | Injects via `Inventory.AddItem()` using dumped IDs | Spawn any item, unlock all blueprints | `F3` |
| **Speedhack / Teleport** | Overrides transform matrix & velocity vectors | Adjust swim speed, jump to coordinates | `F4` |
| **World JSON Dumper** | Scans Unity scene hierarchy & writes to `./dump/` | Reveal map / POI coordinates | `F5` |
| **Waypoint Teleport** | Reads from webmap or saved JSON | Click on map → instant teleport | `F6` |

---

## 📥 Download & Install
> 🔐 **Archive password:** `thalassa2026`

1. Go to the **[Releases](../../releases)** page.
2. Download `Subnautica2_DevTools_Setup_v1.0.0.zip`.
3. Extract using password `thalassa2026`.
4. Launch Subnautica 2, load your save, then run `ThalassaLoader.exe`.
5. Press `F1` – `F6` in game.

---

## 🎮 Quick Start Guide (Video in Mind)

1. **Start game** → load your single‑player save.
2. **Run `ThalassaLoader.exe` as Admin** – you’ll hear a beep and see `[+] Hooks injected`.
3. **Press `F1`** – now the `~` (tilde) key opens the developer console.
4. **Press `F2`** – your health and oxygen become infinite.
5. **Press `F3`** – a GUI appears; select any item and click “Spawn”.
6. **Press `F4`** – toggle 2.5x swim speed.
7. **Press `F5`** – dumps all object IDs and coordinates to `Thalassa_dump/`.
8. **Press `F6`** – teleport to the last waypoint you clicked on the webmap.

> 💡 **Pro tip:** Open the interactive map in your browser (`/docs/webmap/index.html` or the GitHub Pages link). Click any marker → press `F6` to teleport there instantly.

---

## 🛠️ For Developers: AOB Pattern Scanning

We never hardcode addresses. Example from `pattern_scanner.cpp`:

```cpp
uintptr_t FindPlayerController() {
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"UnityPlayer.dll");
    const char* pattern = "48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 48 89 45";
    return PatternScan(moduleBase, pattern);
}
```

This survives game updates because we scan for unique byte signatures.

---

## 🗺️ Interactive Web Map

The repo includes a Leaflet‑based map (`src/webmap/index.html`) that shows:
- Biomes (Safe Shallows, Thermal Spires, etc.)
- Wreck coordinates
- Leviathan spawn zones
- Teleport waypoints

You can host it on GitHub Pages:  
`https://ComptrollerColander.github.io/Subnautica2-Trainer-Console-Commands/src/webmap/`

---

## 🔑 SEO Keywords

`subnautica 2 trainer`, `subnautica 2 console commands`, `subnautica 2 item spawner`, `subnautica 2 cheat`, `il2cpp memory scanner`, `subnautica 2 god mode`, `subnautica 2 speedhack`, `subnautica 2 teleport hack`, `subnautica 2 developer console`, `subnautica 2 mods`.

---

## ❓ FAQ

**Q: Will this get me banned?**  
A: No. Subnautica 2 is single‑player. This tool does not interact with any online services.

**Q: Does it work on Game Pass version?**  
A: Currently only Steam. Game Pass executables have different signatures – open an issue if you want support.

**Q: Why is the ZIP password‑protected?**  
A: To prevent automatic antivirus false‑positive flagging during download. Password is `thalassa2026`.

**Q: The loader says "pattern not found" – what now?**  
A: The game may have updated. Wait for a new release or compile from source with updated patterns.

---

<div align="center">
  <sub>⭐ Star this repo if it helped you – it fuels more updates. Star = love 💚</sub>
</div>
