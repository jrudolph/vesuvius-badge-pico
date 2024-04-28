cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

project(vesuvius-badge)

pico_sdk_init()

add_executable(vesuvius-badge)

target_sources(vesuvius-badge PRIVATE vesuvius.c)

target_link_libraries(vesuvius-badge PRIVATE pico_stdlib hardware_i2c)
pico_add_extra_outputs(vesuvius-badge)
