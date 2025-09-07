cmake_minimum_required(VERSION 3.0)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

project(scapes)

add_subdirectory(${VENDOR_DIR}/glad/)
add_subdirectory(${VENDOR_DIR}/glfw/)
add_subdirectory(${VENDOR_DIR}/glm/)
add_subdirectory(${VENDOR_DIR}/imgui/)

add_executable(${PROJECT_NAME})

file(GLOB_RECURSE PROJECT_SOURCES ${SRC_DIR}/*.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${VENDOR_DIR}/glad ${VENDOR_DIR}/glfw ${VENDOR_DIR}/glm ${VENDOR_DIR}/imgui ${VENDOR_DIR}/stb)
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm imgui imgui-glfw imgui-opengl3 ${CMAKE_DL_LIBS})
