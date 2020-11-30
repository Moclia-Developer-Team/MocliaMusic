mkdir build_x64
cd .\build_x64
cmake -G "Visual Studio 16 2019" -A x64  -DCMAKE_CONFIGURATION_TYPES:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="..\out\install\x64-Release" -DVCPKG_TARGET_TRIPLET=x64-windows-static  -DCMAKE_TOOLCHAIN_FILE="../tools/vcpkg/scripts/buildsystems/vcpkg.cmake" ".."
cmake --build . --config "Release" --target "MocliaMusic"