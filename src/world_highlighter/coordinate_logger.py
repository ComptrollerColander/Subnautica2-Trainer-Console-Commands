import time
import json

def log_coordinates():
    coords = []
    while True:
        # Simulate reading from memory
        x, y, z = 0, 0, 0  # replace with actual memory read
        coords.append({"timestamp": time.time(), "x": x, "y": y, "z": z})
        if len(coords) >= 100:
            with open("coords_log.json", "w") as f:
                json.dump(coords, f, indent=2)
            coords = []
        time.sleep(1)