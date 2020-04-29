cmake_minimum_required(VERSION 3.5.1)

project(gText VERSION 1.0.0)

add_library(NativeTerminal STATIC src/NativeTerminal.c include/NativeTerminal.h)
target_include_directories(NativeTerminal PUBLIC include)

add_library(Input STATIC src/Input.c include/Input.h)
target_include_directories(Input PUBLIC include)


# Build the executable
add_executable(gTed src/main.c)
target_link_libraries(gTed PUBLIC NativeTerminal)
target_link_libraries(gTed PUBLIC Input)
