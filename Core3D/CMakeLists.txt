cmake_minimum_required (VERSION 3.8)

project(Core3D)


add_library(
	Core3D
    Core3DMain.cpp
	)

target_link_libraries(Core3D PUBLIC glfw)
target_link_libraries(Core3D PUBLIC glad)
target_include_directories(Core3D PUBLIC
                          "${PROJECT_SOURCE_DIR}/glad"
                          )

