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
        leetcode/409_longest_palindrome.cpp
        unspecified/virt_functions_play.cpp
        unspecified/inheritance_playground.cpp

)


target_link_libraries(
        ${PROJECT_NAME}
        GTest::gtest_main
)

add_compile_definitions(LOCAL_RUN)

add_subdirectory(yandex-belts/white-belt/1-4)
add_subdirectory(yandex-belts/white-belt/1-5_min)
add_subdirectory(yandex-belts/white-belt/1-5_eq)
add_subdirectory(yandex-belts/white-belt/1-7_1)
add_subdirectory(yandex-belts/white-belt/1-7_2)
add_subdirectory(yandex-belts/white-belt/2-1_1)
add_subdirectory(yandex-belts/white-belt/2-1_2)
add_subdirectory(yandex-belts/white-belt/2-1_3)
add_subdirectory(yandex-belts/white-belt/2-2_1)
add_subdirectory(yandex-belts/white-belt/2-2_2)
add_subdirectory(yandex-belts/white-belt/2-2-3)
add_subdirectory(yandex-belts/white-belt/2-2-4)
add_subdirectory(yandex-belts/white-belt/2-4-1)
add_subdirectory(yandex-belts/white-belt/2-4-2)
add_subdirectory(yandex-belts/white-belt/2-4-3)
add_subdirectory(yandex-belts/white-belt/2-5-1)
add_subdirectory(yandex-belts/white-belt/2-5-2)
add_subdirectory(yandex-belts/white-belt/2-5-3)
add_subdirectory(yandex-belts/white-belt/2-5-4)
add_subdirectory(yandex-belts/white-belt/2-6-1)
add_subdirectory(yandex-belts/white-belt/2-6-2)
add_subdirectory(yandex-belts/white-belt/2-6-3)
add_subdirectory(yandex-belts/white-belt/2-6-4)
add_subdirectory(yandex-belts/white-belt/3-1-1)
add_subdirectory(yandex-belts/white-belt/3-1-2)
add_subdirectory(yandex-belts/white-belt/3-4-1)
add_subdirectory(yandex-belts/white-belt/3-4-2)
add_subdirectory(yandex-belts/white-belt/3-4-3)
add_subdirectory(yandex-belts/white-belt/3-6-1)
add_subdirectory(yandex-belts/white-belt/3-6-2)
add_subdirectory(yandex-belts/white-belt/3-6-3)
add_subdirectory(yandex-belts/white-belt/4-1-1)
add_subdirectory(yandex-belts/white-belt/4-1-2)
add_subdirectory(yandex-belts/white-belt/4-1-3)
add_subdirectory(yandex-belts/white-belt/4-2-1)
add_subdirectory(yandex-belts/white-belt/4-2-2)
add_subdirectory(yandex-belts/white-belt/4-2-3)
add_subdirectory(yandex-belts/white-belt/4-2-4)
add_subdirectory(yandex-belts/white-belt/4-2-5)
add_subdirectory(yandex-belts/white-belt/4-3-1)
add_subdirectory(yandex-belts/white-belt/4-4-1)
add_subdirectory(yandex-belts/white-belt/4-4-2)
add_subdirectory(yandex-belts/white-belt/4-4-3)
add_subdirectory(yandex-belts/white-belt/5)
add_subdirectory(yandex-belts/yellow-belt/1-3-1)
add_subdirectory(yandex-belts/yellow-belt/1-3-2)
add_subdirectory(yandex-belts/yellow-belt/1-4-1)
add_subdirectory(yandex-belts/yellow-belt/1-4-2)
add_subdirectory(yandex-belts/yellow-belt/1-5-1)
add_subdirectory(yandex-belts/yellow-belt/1-5-2)
add_subdirectory(yandex-belts/yellow-belt/2-1-1)
add_subdirectory(yandex-belts/yellow-belt/2-4-1)
add_subdirectory(yandex-belts/yellow-belt/2-4-2)
add_subdirectory(yandex-belts/yellow-belt/2-4-3)
add_subdirectory(yandex-belts/yellow-belt/2-4-4)
add_subdirectory(yandex-belts/yellow-belt/3-2-1)
add_subdirectory(yandex-belts/yellow-belt/phone_number)
add_subdirectory(yandex-belts/yellow-belt/3-3-3)
add_subdirectory(yandex-belts/yellow-belt/4-1-1)
add_subdirectory(yandex-belts/yellow-belt/4-1-2)
add_subdirectory(yandex-belts/yellow-belt/4-1-3)
add_subdirectory(yandex-belts/yellow-belt/4-2-1)
add_subdirectory(yandex-belts/yellow-belt/4-2-2)
add_subdirectory(yandex-belts/yellow-belt/4-2-3)
add_subdirectory(yandex-belts/yellow-belt/4-2-4)
add_subdirectory(yandex-belts/yellow-belt/4-2-5)
add_subdirectory(yandex-belts/yellow-belt/4-3-1)
add_subdirectory(yandex-belts/yellow-belt/4-3-2)
add_subdirectory(yandex-belts/yellow-belt/4-4-1)
add_subdirectory(yandex-belts/yellow-belt/4-4-3)
add_subdirectory(yandex-belts/yellow-belt/4-4-4)
add_subdirectory(yandex-belts/yellow-belt/4-4-5)
add_subdirectory(yandex-belts/yellow-belt/4-4-6)
add_subdirectory(yandex-belts/yellow-belt/5-1-1)
add_subdirectory(yandex-belts/yellow-belt/5-2-1)
add_subdirectory(yandex-belts/yellow-belt/5-2-2)
add_subdirectory(yandex-belts/yellow-belt/5-2-3)
add_subdirectory(yandex-belts/yellow-belt/6)
add_subdirectory(yandex-belts/red-belt/1-2)
add_subdirectory(yandex-belts/red-belt/1-4)




include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})







