cmake_minimum_required(VERSION 2.8)
project(common)
 
include_directories(
    "${PROJECT_SOURCE_DIR}"
)
 
add_library (common
    balance.cpp
	base64.cpp
	bitcryto.cpp
	cfg_reader.cpp
    cjson.cpp
	debug.cpp
	defparser.cpp
	entity.cpp
    entity_mgr.cpp
	epoll_server.cpp
	exception.cpp
	json_helper.cpp
    logger.cpp
	lua_bitset.cpp
	lua_mogo.cpp
	mailbox.cpp
    md5.cpp
	memory_pool.cpp
	mutex.cpp
	net_util.cpp
    path_founder.cpp
	pluto.cpp
	rpc_mogo.cpp
	server_test.cpp
    stopword.cpp
	timer.cpp
	timer_action.cpp
	type_mogo.cpp
    util.cpp
	world.cpp
	xmsg.cpp
	xsem.cpp
)