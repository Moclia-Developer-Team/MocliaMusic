git clone https://github.com/microsoft/vcpkg.git .\tools\vcpkg
cd tools
git clone https://github.com/cyanray/mirai-cpp-vcpkg-port.git .\tools\mirai-cpp-vcpkg-port
cd mirai-cpp-vcpkg-port
copy -r .\tools\mirai-cpp-vcpkg-port\mirai-cpp\ .\tools\vcpkg\ports\mirai-cpp\
cd .\tools\vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
.\vcpkg install cpr:x64-windows-static rapidjson:x64-windows-static fmt:x64-windows-static sqlitecpp:x64-windows-static sqlite3:x64-windows-static mirai-cpp:x64-windows-static