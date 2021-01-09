cmake_minimum_required(VERSION 3.12)  # CMake version check
project(BitBorn)                      # Create project "BitBorn"
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

# Include our FindNcursesw.cmake file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Ncursesw
find_package( PkgConfig REQUIRED )
pkg_check_modules(CURSES ncursesw REQUIRED)
add_compile_definitions(NCURSES_WIDECHAR)

include_directories( ${CURSES_INCLUDE_DIRS} )

# Add CommandLineFPS.cpp file of project root directory as source file
include_directories( include/ )
file(GLOB SOURCES src/*.cpp)

# Copy map to build directory
configure_file(res/Map.dat ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(BitBorn ${SOURCES})

# Link ncursesw library
target_link_libraries( BitBorn ${CURSES_LIBRARIES} )