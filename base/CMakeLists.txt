cmake_minimum_required(VERSION 2.8.9)
project(baseapp)
 
include_directories(./ ../common ../include ../wepoll/include ../cell ../lua)
link_directories(../libs/mysql)

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
	target_link_libraries(baseapp common tinyxml hiredis lua mysqlclient)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()