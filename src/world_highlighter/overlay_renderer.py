import pyautogui
import time
from win32gui import GetWindowText, GetForegroundWindow

def draw_overlay():
    # Placeholder: in real version would use OpenGL/DirectX overlay
    while True:
        if "Subnautica 2" in GetWindowText(GetForegroundWindow()):
            # Mock: move mouse to show coordinates
            x, y = pyautogui.position()
            print(f"\rCoordinates: {x}, {y}", end="")
        time.sleep(0.5)

if __name__ == "__main__":
    draw_overlay()