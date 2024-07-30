# Minimum CMake version required
cmake_minimum_required(VERSION 3.20)

# Project name
project(Makstvell_TCP)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Boost paths
set(BOOST_ROOT "${PROJECT_SOURCE_DIR}/libs/boost")
set(BOOST_INCLUDE_DIR "${BOOST_ROOT}/include")
set(BOOST_LIBRARY_DIR "${BOOST_ROOT}/lib")

# Find Boost
find_package(Boost 1.85 REQUIRED) # Adjust the version as needed

# Check if Boost was found
if (Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/TCP ${Boost_INCLUDE_DIRS})

# Source files
set(SOURCES
    main.cpp
)

# Create the executable
add_executable(Makstvell_TCP ${SOURCES})

# Link Boost libraries (optional, adjust according to which Boost libraries you use)
target_link_libraries(Makstvell_TCP ${Boost_LIBRARIES})
