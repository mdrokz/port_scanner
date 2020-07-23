# CMakeList.txt : CMake project for test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("port_scanner")

# Add source to this project's executable.
add_executable (port_scanner "scanner.c" "scanner.h")
find_package(Threads REQUIRED)
target_link_libraries(port_scanner PRIVATE Threads::Threads)
# VS_DEBUGGER_COMMAND_ARGUMENTS

# TODO: Add tests and install targets if needed.
