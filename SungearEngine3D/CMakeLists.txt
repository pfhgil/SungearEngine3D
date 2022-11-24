cmake_minimum_required (VERSION 3.8)

project(SungearEngine3D)

add_executable(SungearEngine3D 
    SungearEngine3D.cpp
    SungearEngine3D.h
    )


target_link_libraries(SungearEngine3D PUBLIC Core3D)



