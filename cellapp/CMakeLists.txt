cmake_minimum_required(VERSION 2.8.9)
project(cellapp)
 
include_directories(./ ../common ../include ../wepoll/include ../baseapp ../lua)
link_directories(../libs/mysql ../libs/linux)

# Target
add_executable (cellapp
	aoi.cpp
	aoi.h
	cellapp.cpp
	cellapp.h
	entity_cell.cpp
	entity_cell.h
	lua_cell.cpp
	lua_cell.h
	space.cpp
	space.h
	world_cell.cpp
	world_cell.h
	../baseapp/entity_base.cpp
	../baseapp/entity_base.h
	../baseapp/lua_base.cpp
	../baseapp/lua_base.h
	../baseapp/world_base.cpp
	../baseapp/world_base.h
	main.cpp
)

if(MSVC)
	target_link_libraries(cellapp common tinyxml hiredis lua wepoll libmysql ws2_32)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
else()
	target_link_libraries(cellapp common tinyxml hiredis lua mysqlclient uuid dl m libssl.a libcrypto.a)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")
	ADD_DEFINITIONS(-D__RELOGIN -D_CRT_SECURE_NO_WARNINGS)
endif()
