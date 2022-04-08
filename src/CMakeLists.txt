#
# Copyright (C) G2Labs Grzegorz Grzęda - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Grzegorz Grzęda <grzegorz.grzeda@g2labs.pl>, 04.2022
#x
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/message_bus.c)

target_compile_options(${PROJECT_NAME} PRIVATE "-std=c99" "-Wall" "-Wextra" "-Wpedantic" "-Werror")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})