# CMake 版本要求 (最低 3.14)
cmake_minimum_required (VERSION 3.14)

# 项目名称
project(MocliaMusic)
# 设置项目的 C++ 标准
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

# 不要构建 mirai-cpp 自带的 examples
set(MIRAI_CPP_BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
# 添加子模块 mirai-cpp
find_package(mirai-cpp)
find_package(rapidjson)
find_package(cpr)
find_package(SQLiteCpp)

# 源码以 UTF-8 编码保存，使用 MSVC 编译器时需要加编译参数提供支持
if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    message(STATUS "optional: /UTF-8")   
endif(MSVC)

list(APPEND SOURCES src/logo.rc)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/logo.rc) # 递归搜索 src 目录中的源文件, 可根据实际情况修改

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# 设置头文件目录
include_directories(include)
# 链接 mirai-cpp
target_link_libraries(${PROJECT_NAME} PRIVATE mirai-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE SQLiteCpp)
# 使用 mirai-cpp 静态库
target_compile_definitions(${PROJECT_NAME} PRIVATE MIRAICPP_STATICLIB)
# gcc 要连接 pthread
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()
