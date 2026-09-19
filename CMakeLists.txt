cmake_minimum_required(VERSION 3.20)
project(gradebook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(FetchContent)
# FetchContent_Declare(
#     googletest
#     URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
#
# FetchContent_MakeAvailable(googletest)
# enable_testing()
# include(CTest)
# include(GoogleTest)
# add_subdirectory(tests)

add_library(library
    src/utilities.cpp
    src/grading.cpp
    src/printing.cpp
    )
target_include_directories(library PUBLIC include)

add_executable(gradebook app/main.cpp)
target_link_libraries(gradebook PRIVATE library)
