cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)

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
)

add_subdirectory(Dependencies/SDL)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources 
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL/include)

target_link_libraries(${PROJECT_NAME} SDL2)