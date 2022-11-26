cmake_minimum_required (VERSION 3.8)

project(Core3D)
set(public_headers
    include/Core3D/Core3DMain.h
    include/Core3D/GLControl.h
)

add_library(
	Core3D
    "src/Core3DMain.cpp"
    src/GLControl/GLBuffer.cpp
	"src/GLControl/GLShader.cpp" 
    "src/GLControl/GLVertexArray.cpp")

target_link_libraries(Core3D PUBLIC glfw)
target_link_libraries(Core3D PUBLIC glad)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
set_property(TARGET Core3D PROPERTY CXX_STANDARD 17)
