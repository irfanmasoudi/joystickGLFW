.DEFAULT_GOAL=main

main:
	clang++	main.cpp	glad.c	-I./include/	-L./library/	-lglfw3	-framework	Cocoa	-framework	OpenGL	-framework	IOKit	-o	main	-target	arm64-apple-macos11