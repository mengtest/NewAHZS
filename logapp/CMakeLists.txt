cmake_minimum_required(VERSION 2.8.9)
project(logapp)
 
include_directories(./ ../common ../include ../wepoll/include ../cellapp ../baseapp ../lua)
link_directories(../libs/mysql ../libs/linux)

# Target
add_executable (logapp
	api.cpp
	db_task.cpp
	db_task.h
	dboper.cpp
	dboper.h
	http.cpp
	main.cpp
	other.cpp
	other.h
	other_def.h
	threadpool.cpp
	threadpool.h
	world_other.cpp
	world_other.h
)

if(MSVC)
	target_link_libraries(logapp tinyxml hiredis lua wepoll libmysql ws2_32)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
else()
	target_link_libraries(logapp tinyxml hiredis lua mysqlclient uuid dl m libssl.a libcrypto.a)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")
	ADD_DEFINITIONS(-D__RELOGIN -D_CRT_SECURE_NO_WARNINGS)
endif()
