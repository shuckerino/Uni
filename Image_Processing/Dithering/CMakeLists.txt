cmake_minimum_required(VERSION 3.5)

project(Dithering)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV 4.6.0 REQUIRED)

add_executable(Dithering src/main.cpp)

target_link_libraries(Dithering ${OpenCV_LIBS})

# Output message to confirm OpenCV was found
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include path: ${OpenCV_INCLUDE_DIRS}")