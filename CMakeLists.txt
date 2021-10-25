cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)

find_package(SDL2 REQUIRED)

add_subdirectory(Dependencies/SDL)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Engine/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/PrimitiveRenderer/PrimitiveRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Point2D/Point2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/LineSegment/LineSegment.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIB_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

message(${SDL2_INCLUDE_DIRS})