cmake_minimum_required (VERSION 3.8)

project(glad VERSION 4.4) # OGL 4.4 

add_library(
	glad
	glad.c
	glad.h
	khrplatform.h
	) 

