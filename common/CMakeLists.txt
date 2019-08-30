cmake_minimum_required(VERSION 2.8)
project(common)
 

if(MSVC)
	include_directories(./ ../lua ../include ../cell ../base ../include/win)
else()
	include_directories(./ ../lua ../include ../cell ../base)
endif()

# Target
add_library(common
	util.cpp
	util.h
	balance.cpp
	balance.h
	base64.cpp
	base64.h
	bitcryto.cpp
	bitcryto.h
	cfg_reader.cpp
	cfg_reader.h
	cjson.cpp
	cjson.h
	debug.cpp
	debug.h
	defparser.cpp
	defparser.h
	md5.cpp
	md5.h
	json_helper.cpp
	json_helper.h
	logger.cpp
	logger.h
	lua_bitset.cpp
	lua_bitset.h
	lua_mogo.cpp
	lua_mogo.h
	lua_mogo_impl.h
	mailbox.cpp
	mailbox.h
	memory_pool.cpp
	memory_pool.h
	net_util.cpp
	net_util.h
	path_founder.cpp
	path_founder.h
	pluto.cpp
	pluto.h
	rpc_mogo.cpp
	rpc_mogo.h
	stopword.cpp
	stopword.h
	timer.cpp
	timer.h
	timer_action.cpp
	timer_action.h
	type_mogo.cpp
	type_mogo.h
	world.cpp
	world.h
	world_select.h
	epoll_server.cpp
	epoll_server.h
	entity.cpp
	entity.h
	entity_mgr.cpp
	entity_mgr.h
	exception.cpp
	exception.h
	delegate.h
)

if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	ADD_DEFINITIONS(-D__RELOGIN)
endif()
