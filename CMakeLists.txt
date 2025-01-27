cmake_minimum_required(VERSION 3.20)

project(hello-ray VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# dependencies
find_package(fmt CONFIG REQUIRED)

add_executable(${PROJECT_NAME} 
    src/main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)