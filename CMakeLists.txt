cmake_minimum_required(VERSION 3.10)

# Project name
project(reader)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Camera/cereal_log
)

# Source files
set(SOURCES
    controller.cpp
    Camera/cereal_log/ImageMessage.cpp
    Camera/cereal_log/LogReader.cpp
    Camera/cereal_log/Message.cpp
    Camera/cereal_log/TimeStamp.cpp
)

# Header files (optional, for IDE support)
set(HEADERS
    Camera/cereal_log/ImageMessage.h
    Camera/cereal_log/LogReader.h
    Camera/cereal_log/Message.h
    Camera/cereal_log/TimeStamp.h
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
