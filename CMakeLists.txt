cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL"
    GIT_TAG main
)
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_image"
    GIT_TAG main
)
FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf"
    GIT_TAG main
)
FetchContent_Declare(
    SDL2_mixer
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL_mixer"
    GIT_TAG master
)
FetchContent_Declare(
    GLM
    GIT_REPOSITORY "https://github.com/g-truc/glm"
    GIT_TAG master
)

FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_ttf SDL2_mixer GLM)


add_library(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Engine/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/GameObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/DrawableObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/BitmapObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/ModelObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/AnimatedObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/SimpleEventListeningObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/CollidableObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/TransformableObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/GameObjects/TaggedObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/ResourceManager/ResourceManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Animation/Animation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Camera/Camera.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources
    ${sdl2_SOURCE_DIR}
    ${sdl2_image_SOURCE_DIR}
    ${sdl2_ttf_SOURCE_DIR}
    ${sdl2_mixer_SOURCE_DIR}
    ${glm_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image SDL2_ttf SDL2_mixer)
