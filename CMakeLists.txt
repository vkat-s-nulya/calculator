cmake_minimum_required(VERSION 3.14)
project(calculator)

include(FetchContent)
FetchContent_Declare(
    mathlib
    GIT_REPOSITORY https://github.com/vkat-s-nulya/mathlib.git
    GIT_TAG main
)
FetchContent_MakeAvailable(mathlib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(calculator
    src/main.cpp
    src/runner.cpp
    src/parser.cpp
    src/checker.cpp
    src/calculator.cpp
    src/printer.cpp
)

target_link_libraries(calculator PRIVATE mathlib)
install(TARGETS calculator DESTINATION bin)

file(GLOB_RECURSE ALL_SOURCES src/*.cpp src/*.h)

add_custom_target(format
    COMMAND clang-format -i ${ALL_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(tidy
    COMMAND clang-tidy ${ALL_SOURCES} -p ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)