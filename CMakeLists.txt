#
# Copyright (C) G2Labs Grzegorz Grzęda - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Grzegorz Grzęda <grzegorz.grzeda@g2labs.pl>, 03.2022
#
cmake_minimum_required(VERSION 3.5)
project(g2labs-message-bus C)

add_subdirectory(src)

if(DEFINED ENV{PLATFORM})
    add_subdirectory(platform/$ENV{PLATFORM})
endif()