git clone https://github.com/microsoft/vcpkg.git .\tools\vcpkg
git clone https://github.com/cyanray/mirai-cpp-vcpkg-port.git .\tools\mirai-cpp-vcpkg-port
copy -r .\tools\mirai-cpp-vcpkg-port\mirai-cpp\ .\tools\vcpkg\ports\mirai-cpp\
cd .\tools\vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
.\vcpkg install cpr:x86-windows-static rapidjson:x86-windows-static fmt:x86-windows-static sqlitecpp:x86-windows-static sqlite3:x86-windows-static mirai-cpp:x86-windows-static