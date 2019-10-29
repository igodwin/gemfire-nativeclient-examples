cmake_minimum_required(VERSION 3.15)
project(sslputget)

set(CMAKE_CXX_STANDARD 11)

find_package(GeodeNative REQUIRED COMPONENTS cpp crypto)

add_executable(sslputget main.cpp)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        GeodeNative::cpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<SHELL_PATH:$<TARGET_FILE:GeodeNative::crypto>>
        $<SHELL_PATH:$<TARGET_FILE_DIR:${PROJECT_NAME}>>)