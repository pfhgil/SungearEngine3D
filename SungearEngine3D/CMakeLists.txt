cmake_minimum_required (VERSION 3.8)

project(SungearEngine3D) # Объявляем проект

# Добавляем исполняемый файл
add_executable(SungearEngine3D 
    SungearEngine3D.cpp
    SungearEngine3D.h
    )


# Подключаем библиотеку Core3D SungearEngine3D
target_link_libraries(SungearEngine3D PUBLIC Core3D)

set_property(TARGET SungearEngine3D PROPERTY CXX_STANDARD 17)