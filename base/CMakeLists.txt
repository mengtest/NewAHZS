cmake_minimum_required(VERSION 2.8.9)
project(baseapp)
 
include_directories(./ ../common ../include ../wepoll/include ../cell ../lua)
link_directories(../libs/mysql ../libs/linux)

# Target
add_executable (baseapp
	baseapp.cpp
	baseapp.h
	entity_base.cpp
	entity_base.h
	lua_base.cpp
	lua_base.h
	world_base.cpp
	world_base.h
	../cell/entity_cell.cpp
	../cell/entity_cell.h
	../cell/aoi.cpp
	../cell/aoi.h
	../cell/lua_cell.cpp
	../cell/lua_cell.h
	../cell/space.cpp
	../cell/space.h
	../cell/world_cell.cpp
	../cell/world_cell.h
	main.cpp
)

if(MSVC)
	target_link_libraries(baseapp common tinyxml hiredis lua wepoll libmysql ws2_32)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
else()
	target_link_libraries(baseapp common tinyxml hiredis lua mysqlclient uuid dl m libssl.a libcrypto.a)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")
	ADD_DEFINITIONS(-D__RELOGIN -D_CRT_SECURE_NO_WARNINGS)
endif()
