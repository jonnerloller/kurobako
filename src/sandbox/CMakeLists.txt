#not sure if this is the actual version we need, by i'm using Versiopn 3.8 features.
cmake_minimum_required(VERSION 3.8.1)

project (sandbox)

#Set Link flags. Ugly but works. sandbox should only link to kurobako and whatever the game needs that the engine doesnt
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/INCREMENTAL /MANIFEST /DEBUG /MACHINE:X64 /DYNAMICBASE kurobako_d.lib")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL /MANIFEST /DEBUG /DEBUG:FASTLINK kurobako_r.lib")
set(CMAKE_EXE_LINKER_FLAGS_PROFILE "/INCREMENTAL /MANIFEST /DEBUG /MACHINE:X64 /DYNAMICBASE kurobako_p.lib")
set(CMAKE_EXE_LINKER_FLAGS_FINAL "/LTCG /MANIFEST /DEBUG /OPT:REF /MACHINE:X64 /DYNAMICBASE kurobako_final.lib")

#Add manually each time.
#set (SANDBOXSOURCEFILES 
#main.cpp
#)

#auto version
file (GLOB_RECURSE SANDBOXSOURCEFILES *.hpp *.h *.cpp)

set (LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
link_directories("${LIBRARY_OUTPUT_PATH}")
add_executable(sandbox ${SANDBOXSOURCEFILES})

add_dependencies(sandbox kurobako)
set_target_properties(sandbox PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(sandbox PROPERTIES RELEASE_POSTFIX "_r")
set_target_properties(sandbox PROPERTIES PROFILE_POSTFIX "_p")
set_target_properties(sandbox PROPERTIES FINAL_POSTFIX "_final")

set_target_properties(kurobako PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(sandbox PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

target_include_directories(sandbox PUBLIC "../kurobako/")

install(TARGETS sandbox DESTINATION CMAKE_BINARY_DIR)
