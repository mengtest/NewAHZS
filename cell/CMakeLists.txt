cmake_minimum_required(VERSION 2.8.9)
project(cellapp)
 
aux_source_directory(. DIR_CELLAPP_SRCS)
include_directories(./ ../common/header ../include ../wepoll/include ../cell ../lua)
link_directories(../libs/mysql)

# Target
add_executable (cellapp ${DIR_CELLAPP_SRCS})

if(MSVC)
	target_link_libraries(cellapp common tinyxml hiredis lua wepoll libmysql ws2_32)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
else()
	target_link_libraries(cellapp common tinyxml hiredis lua mysqlclient)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()