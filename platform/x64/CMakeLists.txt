#
# Copyright (C) G2Labs Grzegorz Grzęda - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Grzegorz Grzęda <grzegorz.grzeda@g2labs.pl>, 03.2022
#
cmake_minimum_required(VERSION 3.5)
project(g2labs-message-bus-x64)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/main.c)

target_compile_options(${PROJECT_NAME} PRIVATE "-std=c99" "-Wall" "-Wextra" "-Wpedantic" "-Werror")

target_link_libraries(${PROJECT_NAME} g2labs-message-bus)