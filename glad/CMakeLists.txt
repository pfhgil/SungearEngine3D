cmake_minimum_required (VERSION 3.8)

project(glad VERSION 4.4) # OGL 4.4 

add_library(
	glad
	glad.c
	glad.h
	khrplatform.h
	) 

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

