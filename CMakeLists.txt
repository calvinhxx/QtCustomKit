cmake_minimum_required(VERSION 3.6)

# set the project name
project(Example VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add source_files macro function
macro(source_group_by_dir source_files)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR}/)
        foreach(sgbd_file ${${source_files}})
                string(REGEX REPLACE ${sgbd_cur_dir} "" sgbd_fpath ${sgbd_file})
                string(REGEX REPLACE "[^/\\\\]+$" "" sgbd_group_name ${sgbd_fpath})
                if(sgbd_group_name)
                        string(REPLACE "/"   "\\\\"  sgbd_group_name_normal ${sgbd_group_name})
#                        message(STATUS ${sgbd_group_name_normal})
                        source_group(${sgbd_group_name_normal} FILES ${sgbd_file})
                endif(sgbd_group_name)
        endforeach(sgbd_file)
endmacro(source_group_by_dir)

# set default output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/arch")

# main App
add_subdirectory(Example)
# kits library
add_subdirectory(Kits)


