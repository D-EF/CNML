cmake_minimum_required(VERSION 3.10)

project (NML)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

# find_package(WebGL REQUIRED)

file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/**.c"
    "${PROJECT_SOURCE_DIR}/src/**.h"
    "${PROJECT_SOURCE_DIR}/src/**.hpp"
    "${PROJECT_SOURCE_DIR}/src/**.cpp"
)

message(STATUS "SRC_FILES: \n ${SRC_FILES}")

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

# target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)