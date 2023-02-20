# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
include($ENV{ADF_PATH}/CMakeLists.txt)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-field-initializers -funsigned-char -w -Wfatal-errors -Wno-unused-variable -std=gnu++17")
project(FreeK)
