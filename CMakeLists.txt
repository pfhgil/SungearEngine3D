cmake_minimum_required (VERSION 3.8)


add_subdirectory("Core3D")
add_subdirectory("SungearEngine3D")

project(SungearEngine3D)

add_executable(SungearEngine3D 
    SungearEngine3D/SungearEngine3D.cpp
    SungearEngine3D/SungearEngine3D.h
    )

target_link_libraries(SungearEngine3D PUBLIC Core3D)

target_include_directories(SungearEngine3D PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Core3D"
                          )


