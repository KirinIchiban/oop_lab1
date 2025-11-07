cmake_minimum_required(VERSION 3.10)
project(lab3 LANGUAGES CXX)

add_compile_options(-Wall)    

add_library(lab3_lib src/array.cpp src/point.cpp src/trapeze.cpp src/rhomb.cpp src/pentagon.cpp)
target_include_directories(lab3_lib PUBLIC include)
add_executable(lab3_exe main.cpp)
target_link_libraries(lab3_exe PRIVATE lab3_lib)

#для тестов
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(my-tests test/tests3.cpp) 
target_link_libraries(my-tests ${CMAKE_PROJECT_NAME}_lib gtest_main)
add_test(NAME GTests COMMAND my-tests)