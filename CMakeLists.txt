cmake_minimum_required(VERSION 3.14)
project(calculator)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)
if(ENABLE_TSAN)
    add_compile_options(-fsanitize=thread -g)
    add_link_options(-fsanitize=thread)
endif()

include(FetchContent)
FetchContent_Declare(
    mathlib
    GIT_REPOSITORY https://github.com/vkat-s-nulya/mathlib.git
    GIT_TAG main
)
FetchContent_MakeAvailable(mathlib)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

find_package(PostgreSQL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(Threads REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(calculator
    src/main.cpp
    src/runner.cpp
    src/parser.cpp
    src/checker.cpp
    src/calculator.cpp
    src/logger.cpp
    src/database.cpp
    src/cache.cpp
    src/types.cpp
    src/server.cpp
    src/session.cpp
)

target_link_libraries(calculator PRIVATE
    mathlib
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    PostgreSQL::PostgreSQL
    Boost::system
    Threads::Threads
)
install(TARGETS calculator DESTINATION bin)

set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1")
include(CTest)

add_executable(tests
    tests/test_parser.cpp
    tests/test_checker.cpp
    tests/test_calculator.cpp
    tests/test_server.cpp
    src/parser.cpp
    src/checker.cpp
    src/calculator.cpp
    src/logger.cpp
    src/types.cpp
    src/runner.cpp
    src/database.cpp
    src/cache.cpp
    src/server.cpp
    src/session.cpp
)

target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE
    mathlib
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    PostgreSQL::PostgreSQL
    Boost::system
    Threads::Threads
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

file(GLOB_RECURSE ALL_SOURCES src/*.cpp src/*.h tests/*.cpp)

add_custom_target(format
    COMMAND clang-format -i ${ALL_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(tidy
    COMMAND clang-tidy ${ALL_SOURCES} -p ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)