cmake_minimum_required(VERSION 3.14)
project(SpellChecker VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(SpellCheckerCore STATIC
    src/Dictionary.cpp
    src/EditDistance.cpp
    src/Tokenizer.cpp
    src/utils.cpp
)

target_include_directories(SpellCheckerCore PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SpellCheckerCore)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()