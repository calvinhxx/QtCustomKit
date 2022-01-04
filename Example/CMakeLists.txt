cmake_minimum_required(VERSION 3.6)

# set the project name
project(Example)

# set app name
set(NAME App)

# set output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/release)

# find 3d package 
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# find files recurse
file(GLOB_RECURSE All_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group_by_dir(All_SOURCES)
foreach(v ${All_SOURCES})
    message(${v})
endforeach()

# set include dir
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../Kits/include )

# set compile options
#target_compile_options()

if(WIN32)
    set(LINK_LIBRARY Kits )
elseif(APPLE)
    set(LINK_LIBRARY Kits )
endif()

# create the executable
add_executable(${NAME} ${All_SOURCES} )

# link lib
target_link_libraries(${NAME} ${LINK_LIBRARY} Qt5::Core Qt5::Widgets)
