cmake_minimum_required(VERSION 3.10)

project(amxx_bcrypt LANGUAGES CXX)

set(AMXMODX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/amxmodx)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    sdk
    bcrypt_lib
)

include_directories(
    ${AMXMODX_DIR}/public
)

set(PROJECT_SOURCES
    amxx_bcrypt.cpp
    sdk/amxxmodule.cpp
    bcrypt_lib/bcrypt.cpp
    bcrypt_lib/blowfish.cpp
)

add_library(amxx_bcrypt SHARED ${PROJECT_SOURCES})

target_compile_definitions(amxx_bcrypt PRIVATE HAVE_STDINT_H)

if(WIN32)
    set_target_properties(amxx_bcrypt PROPERTIES OUTPUT_NAME "bcrypt_amxx")
    target_compile_definitions(amxx_bcrypt PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    set_target_properties(amxx_bcrypt PROPERTIES OUTPUT_NAME "bcrypt_amxx_i386")
    set_target_properties(amxx_bcrypt PROPERTIES PREFIX "")
    target_compile_options(amxx_bcrypt PRIVATE -m32 -fPIC)
    target_link_options(amxx_bcrypt PRIVATE -m32 -static-libstdc++ -static-libgcc)
endif()