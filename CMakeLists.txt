cmake_minimum_required(VERSION 3.27)
project(hptp_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include(${HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
find_package(Poco REQUIRED Foundation Net)
find_package(Boost REQUIRED )


add_executable(main_transmit ${CMAKE_CURRENT_SOURCE_DIR}/unix/transmitter/main.cpp)
target_link_libraries(main_transmit Poco Boost)

add_executable(main_receive ${CMAKE_CURRENT_SOURCE_DIR}/unix/receiver/main.cpp)
target_link_libraries(main_receive Poco Boost)