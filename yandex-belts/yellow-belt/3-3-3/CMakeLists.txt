cmake_minimum_required(VERSION 3.25)
project(yandex-yellow-3-3-3)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCES
    main.cpp
    query.cpp
    query.h
    responces.cpp
    responces.h
    bus_manager.cpp
    bus_manager.h
)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
