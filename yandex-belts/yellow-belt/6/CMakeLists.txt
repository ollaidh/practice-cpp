cmake_minimum_required(VERSION 3.25)
project(yandex-yellow-6)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
main.cpp
date.cpp
database.cpp
node.cpp
condition_parser.cpp
token.cpp
)
