cmake_minimum_required(VERSION 3.10)
project(lab7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Устанавливаем флаги компилятора
add_compile_options(-g -rdynamic)

# Подключаем SFML только для основной программы
find_package(SFML 2.5 REQUIRED graphics window system)

# Подключаем Google Test
add_subdirectory(lib/googletest)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIR})

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

# Собираем все исходные файлы
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

# Создаём библиотеку
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})

# Создаём исполняемый файл для основной программы
add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib sfml-graphics sfml-window sfml-system)

# Создаём исполняемый файл для тестов, без SFML
add_executable(${CMAKE_PROJECT_NAME}_test ${TEST_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME}_test PRIVATE ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest gtest_main sfml-graphics sfml-window sfml-system)
