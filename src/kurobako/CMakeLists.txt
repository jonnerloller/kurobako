#not sure if this is the actual version we need, by i'm using Versiopn 3.8 features.
cmake_minimum_required(VERSION 3.8.1)

project (kurobako) #kurobako is black box

#Link config file. There are better ways to do this but i'm too lazy to fully master cmake.
configure_file(
    "${CMAKE_SOURCE_DIR}/kurobakoconfig.h.in"
    "${CMAKE_SOURCE_DIR}/src/kurobako/kurobakoconfig.h"
)

#Not 100% working. still figuring out linking libraries into the engine
set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "/LTCG /MACHINE:X64")
set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "/LTCG /MACHINE:X64")
set(CMAKE_STATIC_LINKER_FLAGS_PROFILE "/LTCG /MACHINE:X64")
set(CMAKE_STATIC_LINKER_FLAGS_FINAL "/LTCG /MACHINE:X64")

#includes
include_directories("$(CMAKE_SOURCE_DIR)/src")

#Add manually each time.
set (KUROBAKOSOURCEFILES 
kurobakoconfig.h
enginemain.h enginemain.cpp
graphics/teststructure.cpp
)

#auto version
#file (GLOB_RECURSE KUROBAKOSOURCEFILES *.h *.cpp)

set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
#build kurobako
add_library(kurobako STATIC ${KUROBAKOSOURCEFILES})
set_target_properties(kurobako PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(kurobako PROPERTIES RELEASE_POSTFIX "_r")
set_target_properties(kurobako PROPERTIES PROFILE_POSTFIX "_p")
set_target_properties(kurobako PROPERTIES FINAL_POSTFIX "_final")

target_include_directories(kurobako PUBLIC $(CMAKE_CURRENT_SOURCE_DIR))

install(TARGETS kurobako DESTINATION LIBRARY_OUTPUT_PATH)