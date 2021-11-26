cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL"
    GIT_TAG main
)
FetchContent_GetProperties(SDL2)
if (NOT sdl2_POPULATED)
    FetchContent_Populate(SDL2)
    add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR})
endif ()

FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image"
    GIT_TAG main
)
FetchContent_GetProperties(SDL2_image)
if (NOT sdl2_image_POPULATED)
    FetchContent_Populate(SDL2_image)
    add_subdirectory(${sdl2_image_SOURCE_DIR} ${sdl2_image_BINARY_DIR})
endif ()

FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf"
    GIT_TAG main
)
FetchContent_GetProperties(SDL2_ttf)
if (NOT sdl2_ttf_POPULATED)
    FetchContent_Populate(SDL2_ttf)
    add_subdirectory(${sdl2_ttf_SOURCE_DIR} ${sdl2_ttf_BINARY_DIR})
endif ()

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Engine/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/PrimitiveRenderer/PrimitiveRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Point2D/Point2D.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/LineSegment/LineSegment.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Utility/Color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/BitmapRenderer/BitmapRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/GameObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/BitmapObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/ModelObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Testing/TestingGameObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/AnimatedObject.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sources)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf)