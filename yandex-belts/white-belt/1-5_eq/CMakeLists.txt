cmake_minimum_required(VERSION 3.25)
project(yandex-white-1-5_eq)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.13.0
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} 1-5_eq.cpp)

target_link_libraries(
        ${PROJECT_NAME}
        GTest::gtest_main
)
