cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cmake/sdl2)


find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Engine/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/PrimitiveRenderer/PrimitiveRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Point2D/Point2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/LineSegment/LineSegment.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sources)

target_link_libraries(${PROJECT_NAME} SDL2::Main)
