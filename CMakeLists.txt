cmake_minimum_required(VERSION 3.12)
project(all-test)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES_TEST
./test/test.cpp
./src/SimpleTest.h
./src/SimpleTest.cpp
		)

set(CMAKE_CXX_FLAGS --coverage)
add_executable(run-test ${SOURCE_FILES_TEST})

set(SOURCE_FILES_EXAMPLE
		./example/example.cpp
		./src/SimpleTest.h
		./src/SimpleTest.cpp
		)
add_executable(run-example ${SOURCE_FILES_EXAMPLE}
		)
