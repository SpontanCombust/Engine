cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cmake/sdl2)

find_package(SDL2 REQUIRED)

find_package(SDL2_gfx REQUIRED)



add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PrimitiveRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${PROJECT_NAME} SDL2::Main)
target_link_libraries(${PROJECT_NAME} SDL2::GFX)
