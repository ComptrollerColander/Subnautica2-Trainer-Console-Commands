import tkinter as tk
from tkinter import ttk
import json

class SpawnerGUI:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Subnautica 2 Item Spawner")
        self.root.geometry("400x500")
        self.root.configure(bg="#0b2b40")

        with open("docs/map_data/items.json", "r") as f:
            self.items = json.load(f)

        tk.Label(self.root, text="Select Item:", fg="#00ffcc", bg="#0b2b40", font=("Consolas", 12)).pack(pady=10)
        self.combo = ttk.Combobox(self.root, values=list(self.items.keys()), width=40)
        self.combo.pack(pady=5)

        tk.Button(self.root, text="Spawn Item", command=self.spawn, bg="#004466", fg="white").pack(pady=20)
        self.root.mainloop()

    def spawn(self):
        item_name = self.combo.get()
        if not item_name:
            return
        # In real version: call into memory injection
        print(f"[GUI] Spawning {item_name} ({self.items[item_name]})")

if __name__ == "__main__":
    SpawnerGUI()