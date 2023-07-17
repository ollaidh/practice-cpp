cmake_minimum_required(VERSION 3.25)
set(PROJECT_NAME practice-cpp)
project(${PROJECT_NAME})

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

add_executable(${PROJECT_NAME}
        main.cpp

        streams.cpp
        array_on_stack_test.cpp

        unspecified/square_function.cpp

        leetcode/two_sum.cpp
        leetcode/two_arrays_intersect.cpp
        leetcode/underground_system.cpp
        leetcode/atm_machine.cpp
        leetcode/14_longest_common_prefix.cpp
        leetcode/58_length_last_word.cpp
        leetcode/119_pascal_triangle_II.cpp
        leetcode/169_majority_element.cpp
        leetcode/205_isomorphic_strings.cpp
        leetcode/268_missing_number.cpp
        leetcode/448_numbers_disappeared_in_arr.cpp
        leetcode/496_next_greater_element_I.cpp

        learncpp/4-12_prime_numbers.cpp
        learncpp/4-12_prime_numbers.cpp
        learncpp/4-12_prime_numbers.cpp

        HackerRank/overload_ostream_operator.cpp
        leetcode/409_longest_palindrome.cpp)

target_link_libraries(
        ${PROJECT_NAME}
        GTest::gtest_main
)