cmake_minimum_required(VERSION 3.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

project(scapes)

add_subdirectory(${VENDOR_DIR}/glad/)
add_subdirectory(${VENDOR_DIR}/glfw/)
add_subdirectory(${VENDOR_DIR}/glm/)
add_subdirectory(${VENDOR_DIR}/imgui/)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Application.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Clock.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Engine.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Input.cpp)

target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/AABB.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Camera.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Cubemap.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Object.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Shader.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Skybox.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Sprite.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Texture.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Tilemap.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Transform.cpp)

target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/manager/BlockManager.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/manager/ChunkManager.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/manager/EntityManager.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/manager/ShaderManager.cpp)

target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/player/Raycast.cpp)

target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/view/Camera2D.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/view/Camera3D.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/view/CameraPlayer.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/view/Renderer.cpp)

target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/world/Block.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/world/Chunk.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/world/Entity.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/world/World.cpp)

target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${VENDOR_DIR}/glad ${VENDOR_DIR}/glfw ${VENDOR_DIR}/glm ${VENDOR_DIR}/imgui ${VENDOR_DIR}/stb)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm imgui imgui-glfw imgui-opengl3 ${CMAKE_DL_LIBS})
