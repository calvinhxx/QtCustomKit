cmake_minimum_required(VERSION 3.6)

# set the project name
project(Kits)

# set lib name
set(NAME Kits)

set(CMAKE_AUTOMOC ON)

# find 3d package 
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# find files recurse
file(GLOB_RECURSE All_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
source_group_by_dir(All_SOURCES)
foreach(v ${All_SOURCES})
    message(${v})
endforeach()

# set include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# create share lib
if(WIN32)
    add_library(${NAME} SHARED ${All_SOURCES})
elseif(APPLE)
    add_library(${NAME} SHARED ${All_SOURCES})
    set_target_properties(${NAME} PROPERTIES
      FRAMEWORK TRUE
      FRAMEWORK_VERSION A # Version "A" is macOS convention
      MACOSX_FRAMEWORK_IDENTIFIER org.cmake.${NAME}
    )
endif()

# lib link qtlib
target_link_libraries(${NAME} Qt5::Core Qt5::Widgets )


