cmake_minimum_required(VERSION 3.25.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_CXX_COMPILER clang++)

# set path to vcpkg
set(CMAKE_PREFIX_PATH "/home/owos/vcpkg/installed/x64-linux")
include_directories("/home/owos/vcpkg/installed/x64-linux/include")

# header files & packages
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
find_package(Poco REQUIRED COMPONENTS Foundation Net)


project(http_include)
add_executable(http_mod ${CMAKE_CURRENT_SOURCE_DIR}/include/common/http_mod.cpp)