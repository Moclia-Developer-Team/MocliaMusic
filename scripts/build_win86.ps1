mkdir build_x86
cd .\build_x86
cmake -G "Visual Studio 16 2019" -A x86  -DCMAKE_CONFIGURATION_TYPES:STRING="Release" -DCMAKE_INSTALL_PREFIX:PATH="..\out\install\x86-Release" -DVCPKG_TARGET_TRIPLET=x86-windows-static  -DCMAKE_TOOLCHAIN_FILE="../tools/vcpkg/scripts/buildsystems/vcpkg.cmake" ".."
cmake --build . --config "Release" --target "MocliaMusic"