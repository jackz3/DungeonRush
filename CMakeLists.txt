cmake_minimum_required(VERSION 3.5.1)
project(DungeonRush VERSION 0.1.0
                    DESCRIPTION "A game inspired by snake"
                    LANGUAGES C)

# Set output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(ENABLE_LAN "Build LAN multiplayer support" OFF)
option(ENABLE_AUDIO "Build audio support" ON)

# if(APPLE)
#     set(HOMEBREW_PREFIX "/opt/homebrew")
#     if(EXISTS "${HOMEBREW_PREFIX}/lib/cmake/SDL3/SDL3Config.cmake")
#         set(SDL3_DIR "${HOMEBREW_PREFIX}/lib/cmake/SDL3" CACHE PATH "SDL3 package config path" FORCE)
#     endif()
#     if(EXISTS "${HOMEBREW_PREFIX}/lib/cmake/SDL3_image/SDL3_imageConfig.cmake")
#         set(SDL3_image_DIR "${HOMEBREW_PREFIX}/lib/cmake/SDL3_image" CACHE PATH "SDL3_image package config path" FORCE)
#     endif()
#     if(EXISTS "${HOMEBREW_PREFIX}/lib/cmake/SDL3_ttf/SDL3_ttfConfig.cmake")
#         set(SDL3_ttf_DIR "${HOMEBREW_PREFIX}/lib/cmake/SDL3_ttf" CACHE PATH "SDL3_ttf package config path" FORCE)
#     endif()
#     if(EXISTS "${HOMEBREW_PREFIX}/lib/cmake/SDL3_mixer/SDL3_mixerConfig.cmake")
#         set(SDL3_mixer_DIR "${HOMEBREW_PREFIX}/lib/cmake/SDL3_mixer" CACHE PATH "SDL3_mixer package config path" FORCE)
#     endif()
#     if(EXISTS "${HOMEBREW_PREFIX}/lib/cmake/SDL3_net/SDL3_netConfig.cmake")
#         set(SDL3_net_DIR "${HOMEBREW_PREFIX}/lib/cmake/SDL3_net" CACHE PATH "SDL3_net package config path" FORCE)
#     endif()
# endif()

# Find SDL3
find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

if(ENABLE_AUDIO)
    find_package(SDL3_mixer REQUIRED CONFIG)
endif()

if(ENABLE_LAN)
    find_package(SDL3_net REQUIRED CONFIG)
endif()

set(BIN_NAME dungeon_rush)

file(GLOB SRC src/*.c)

add_executable(${BIN_NAME} ${SRC})

target_include_directories(${BIN_NAME} PUBLIC src)
target_link_libraries(${BIN_NAME} PRIVATE SDL3::SDL3-shared SDL3_image::SDL3_image
                                            SDL3_ttf::SDL3_ttf m)

if(ENABLE_AUDIO)
    target_compile_definitions(${BIN_NAME} PRIVATE ENABLE_AUDIO=1)
    target_link_libraries(${BIN_NAME} PRIVATE SDL3_mixer::SDL3_mixer)
else()
    target_compile_definitions(${BIN_NAME} PRIVATE ENABLE_AUDIO=0)
endif()

if(ENABLE_LAN)
    target_compile_definitions(${BIN_NAME} PRIVATE ENABLE_LAN=1)
    target_link_libraries(${BIN_NAME} PRIVATE SDL3_net::SDL3_net)
else()
    target_compile_definitions(${BIN_NAME} PRIVATE ENABLE_LAN=0)
endif()

file(COPY res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
