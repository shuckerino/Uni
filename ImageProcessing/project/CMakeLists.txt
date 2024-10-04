cmake_minimum_required(VERSION 3.0)
project(opencv_test)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add the executable
add_executable(test test.cpp)

# Link the OpenCV libraries to your project
target_link_libraries(test ${OpenCV_LIBS})

# Include the OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})
