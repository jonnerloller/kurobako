#not sure if this is the actual version we need, by i'm using Versiopn 3.8 features.
cmake_minimum_required(VERSION 3.8.1)

project (blackbox)

#Setup Build Configs.
if(NOT SET_UP_CONFIGURATIONS_DONE)
    set(SET_UP_CONFIGURATIONS_DONE 1)

    # No reason to set CMAKE_CONFIGURATION_TYPES if it's not a multiconfig generator
    # Also no reason mess with CMAKE_BUILD_TYPE if it's a multiconfig generator.
    if(CMAKE_CONFIGURATION_TYPES) # multiconfig generator?
        set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile;Final" CACHE STRING "" FORCE) 
    else()
        if(NOT CMAKE_BUILD_TYPE)
            message("Defaulting to release build.")
            set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
        endif()
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose the type of build")
        # set the valid options for cmake-gui drop-down list
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;Profile;Final")
    endif()

    #I am very very sure there is a better way to do this, but the problem i am facing is as such.
    #I want do define a different Define for every configuration. couldn't figure it out.
    #This weems to work.
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /fp:precise /GR /Zi /DKUROBAKODEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /fp:precise /GR /Zi /DKUROBAKORELEASE")
    set(CMAKE_CXX_FLAGS_PROFILE "/O2 /Ob2 /Ot /GR /fp:precise /Zi /DKUROBAKOPROFILE")
    set(CMAKE_CXX_FLAGS_FINAL "/Ox /Ob2 /Ot /GL /GR- /fp:fast /Zi /DKUROBAKOFINAL")

    #Make sure that we have the proper suffixes
    set_property (TARGET ${LIB_NAME} PROPERTY DEBUG_POSTFIX d)
    set_property (TARGET ${LIB_NAME} PROPERTY RELEASE_POSTFIX r)
    set_property (TARGET ${LIB_NAME} PROPERTY PROFILE_POSTFIX p)
    set_property (TARGET ${LIB_NAME} PROPERTY FINAL_POSTFIX f)
endif()


#general compile options.
add_compile_options(/arch:AVX2)
add_compile_options(/MD)
add_compile_options(/EHsc)
add_compile_options(/W3)
add_compile_options(/std:c++latest)
add_compile_options(/MP)

#Output Folders
set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

#Legit if I don't do this... dumb shit happens, i.e it defaults to bin/config/target.exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_PROFILE ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_FINAL ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY_FINAL ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(kurobako)
add_subdirectory(sandbox)


