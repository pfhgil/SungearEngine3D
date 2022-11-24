cmake_minimum_required (VERSION 3.8)

project(Core3D)


add_library(
	Core3D
    "src/Core3DMain.cpp"
    "Core3D/Core3DMain.h"
	)

target_link_libraries(Core3D PUBLIC glfw)
target_link_libraries(Core3D PUBLIC glad)


set(public_headers
    include/Core3D/Core3DMain.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

