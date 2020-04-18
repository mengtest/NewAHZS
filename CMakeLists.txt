cmake_minimum_required(VERSION 2.8.9)
project(NewAHZS)
set(CMAKE_VERBOSE_MAKEFILE OFF)
# Add the source in project root directory
aux_source_directory(. DIRSRCS)
# Add header file include directories
include_directories(./ ./include ./include/mysql/ ./tinyxml ./common/header ./lua ./wepoll/include ./wepoll/src ./wepoll/src/regular ./wepoll/src/combined )
if(MSVC)
	include_directories(hiredis/win include/win)
else()
	include_directories(hiredis/linux)
endif()
# Add block directories
add_subdirectory(tinyxml)
add_subdirectory(lua)
add_subdirectory(common)
add_subdirectory(cwmd)
add_subdirectory(baseapp)
add_subdirectory(cellapp)
add_subdirectory(loginapp)
add_subdirectory(logapp)



if(MSVC)
	add_subdirectory(wepoll)
	add_subdirectory(hiredis/win)
else()
	add_subdirectory(hiredis/linux)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=c++11)
endif()
