@echo off
echo Installing Python dependencies...
pip install pyautogui pypiwin32 requests
echo Installing vcpkg for C++ (if needed)
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install minhook
cd ..
echo Done.
pause