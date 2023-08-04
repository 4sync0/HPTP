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
find_package(Poco REQUIRED COMPONENTS Foundation Net REQUIRED)
find_package(Boost REQUIRED)


project(messageSendReceiveProject)

add_executable(http_transmit ${CMAKE_CURRENT_SOURCE_DIR}/unix/transmitter/main.cpp)
target_link_libraries(http_transmit Poco::Foundation Poco::Net)

add_executable(http_receive ${CMAKE_CURRENT_SOURCE_DIR}/unix/receiver/main.cpp)
target_link_libraries(http_receive Poco::Foundation Poco::Net)