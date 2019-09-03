cmake_minimum_required(VERSION 2.8.9)
project(syncdb)
 
include_directories(./ ../common ../include ../wepoll/include ../cell ../base ../lua )
link_directories(../libs/mysql ../libs/linux)

# Target
add_executable (syncdb
	../dbmgr/dboper.cpp
	../dbmgr/dboper.h
	../dbmgr/world_dbmgr.cpp
	../dbmgr/world_dbmgr.h
	../dbmgr/db_task.cpp
	../dbmgr/db_task.h
	../dbmgr/myredis.cpp
	../dbmgr/myredis.h
	main.cpp
)

if(MSVC)
	target_link_libraries(syncdb common tinyxml hiredis lua wepoll libmysql ws2_32)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
else()
	target_link_libraries(syncdb common tinyxml hiredis lua mysqlclient uuid dl m libssl.a libcrypto.a)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")
	ADD_DEFINITIONS(-D__RELOGIN -D_CRT_SECURE_NO_WARNINGS)
endif()
