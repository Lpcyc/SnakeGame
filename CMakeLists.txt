cmake_minimum_required(VERSION 3.10)
project(SnakeGame)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(SnakeGame
	main.cpp
	game.cpp 
	game.h
	map.cpp 
	map.h 
	snake.cpp 
	snake.h
)