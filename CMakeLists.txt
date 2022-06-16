cmake_minimum_required(VERSION 3.0)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

project(scapes)

add_subdirectory(${LIB_DIR}/glad/)
add_subdirectory(${LIB_DIR}/glfw/)
add_subdirectory(${LIB_DIR}/glm/)
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Application.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/core/Engine.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${SRC_DIR}/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_DIR}/glad ${LIB_DIR}/glfw ${LIB_DIR}/glm ${LIB_DIR}/imgui ${LIB_DIR}/stb)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm ${CMAKE_DL_LIBS})
