cmake_minimum_required(VERSION 3.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

project(scapes)

add_subdirectory(${VENDOR_DIR}/glad/)
add_subdirectory(${VENDOR_DIR}/glfw/)
add_subdirectory(${VENDOR_DIR}/glm/)
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Application.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Clock.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Engine.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Input.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Shader.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/gl/Texture.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/world/Sprite.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${VENDOR_DIR}/glad ${VENDOR_DIR}/glfw ${VENDOR_DIR}/glm ${VENDOR_DIR}/imgui ${VENDOR_DIR}/stb)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm ${CMAKE_DL_LIBS})
