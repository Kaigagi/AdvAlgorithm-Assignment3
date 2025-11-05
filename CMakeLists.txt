cmake_minimum_required(VERSION 3.0...3.5)

# Define the project name and language
project(flow_graph LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Helpful for editors like VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler flags for gcc/clang
add_compile_options(
#  -Wall
#  -Wextra
# -Werror
# -pedantic-errors
# -Wconversion
# -Wsign-conversion
# -Wdouble-promotion
# -Wcast-align
# -Wformat=2
# -Wuninitialized
# -Wnull-dereference
# -Wnon-virtual-dtor
# -Woverloaded-virtual
# -Wdeprecated-copy-dtor
# -Wold-style-cast
# -Wsuggest-override
# -fstack-protector-strong
)

# Debug builds with sanitizers
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")

# Fetch and set up Google Test
include(FetchContent)
FetchContent_Declare(
 googletest
 URL https://github.com/google/googletest/archive/7321f950dfe0d481b56b1c475e38b681ff34263f.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
include(CTest)
include(GoogleTest)
enable_testing()

# Create library
add_library(flow_graph 
    FlowGraph.cpp
    KargerMinCut.cpp
    UnionFind.cpp
    EdmondsKarp.cpp
)

target_include_directories(flow_graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Create test executable
add_executable(tests 
    KargerTest.cpp
    EdmondsKarpTest.cpp
    main.cpp
)
target_link_libraries(tests 
    PRIVATE 
    flow_graph 
    gtest_main
)

# Discover and add tests
gtest_discover_tests(tests)
