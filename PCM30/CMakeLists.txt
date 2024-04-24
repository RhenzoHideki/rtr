cmake_minimum_required(VERSION 3.13)
project(receiverE1)

set(CMAKE_CXX_STANDARD 11)
include_directories(.)

add_executable(receiverE1 main.cpp alinhador.cpp pamq.cpp)

add_custom_target(run
    COMMAND receiverE1
    DEPENDS receiverE1
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)