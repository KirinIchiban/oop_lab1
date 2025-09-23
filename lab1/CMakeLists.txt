cmake_minimum_required(VERSION 3.10)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall)    

add_library(lab1_lib src/solution1.cpp)
target_include_directories(lab1_lib PUBLIC include)
add_executable(lab1_exe src/main.cpp)
target_link_libraries(lab1_exe PRIVATE lab1_lib)

#для тестов
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(my-tests test/tests1.cpp) #собрали файл с тестами
target_link_libraries(my-tests ${CMAKE_PROJECT_NAME}_lib gtest_main)
add_test(NAME GTests COMMAND my-tests)