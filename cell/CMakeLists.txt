cmake_minimum_required(VERSION 2.8.9)
project(cellapp)
 
include_directories(./ ../common ../include ../wepoll/include ../base ../lua)
link_directories(../libs/mysql)

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
	../base/entity_base.cpp
	../base/entity_base.h
	../base/lua_base.cpp
	../base/lua_base.h
	../base/world_base.cpp
	../base/world_base.h
	main.cpp
)

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