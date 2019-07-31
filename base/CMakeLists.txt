cmake_minimum_required(VERSION 2.8)
project(baseapp)
 
include_directories(./ ../common/header ../include ../wepoll/include ../cell ../lua)
 
include_directories(
    "${PROJECT_SOURCE_DIR}"
)
 
add_executable (baseapp
	baseapp.cpp
	baseapp.h
	entity_base.cpp
	entity_base.h
	lua_base.cpp
	lua_base.h
	world_base.cpp
	world_base.h
	main.cpp
)

if(MSVC)
	target_link_libraries(baseapp wepoll ../include/mysql/libmysql.lib)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
else()

endif()

target_link_libraries(baseapp tinyxml hiredis common lua )
