cmake_minimum_required(VERSION 2.8.2)
add_executable(travis_test
	main.cpp
)
target_link_libraries(travis_test gtest)
