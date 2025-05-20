cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание статической библиотеки banking
add_subdirectory(banking)

# Опция для включения тестов
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    
    # Подключаем Google Test
    add_subdirectory(third-party/gtest)
    
    # Ищем исходники тестов
    file(GLOB TEST_SOURCES tests/*.cpp)
    
    # Создаем тестовый исполняемый файл
    add_executable(check ${TEST_SOURCES})
    
    # Линкуем с библиотеками
    target_link_libraries(check PRIVATE banking gtest_main gmock)
    target_link_libraries(check PRIVATE banking gtest_main)
    
    # Добавляем тест в CTest
    add_test(NAME banking_tests COMMAND check)
endif()
