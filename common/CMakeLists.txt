cmake_minimum_required(VERSION 2.8)
project(common)
 
include_directories(./ ./header ../lua ../include ../cell ../base)

set(HEADER_FILES_PREFIX header)
set(HEADER_FILES
	${HEADER_FILES_PREFIX}/util.h
	${HEADER_FILES_PREFIX}/balance.h
	${HEADER_FILES_PREFIX}/base64.h
	${HEADER_FILES_PREFIX}/bitcryto.h
	${HEADER_FILES_PREFIX}/cfg_reader.h
	${HEADER_FILES_PREFIX}/cjson.h
	${HEADER_FILES_PREFIX}/debug.h
	${HEADER_FILES_PREFIX}/defparser.h
	${HEADER_FILES_PREFIX}/md5.h
	${HEADER_FILES_PREFIX}/json_helper.h
	${HEADER_FILES_PREFIX}/logger.h
	${HEADER_FILES_PREFIX}/lua_bitset.h
	${HEADER_FILES_PREFIX}/lua_mogo.h
	${HEADER_FILES_PREFIX}/lua_mogo_impl.h
	${HEADER_FILES_PREFIX}/mailbox.h
	${HEADER_FILES_PREFIX}/memory_pool.h
	${HEADER_FILES_PREFIX}/net_util.h
	${HEADER_FILES_PREFIX}/path_founder.h
	${HEADER_FILES_PREFIX}/pluto.h
	${HEADER_FILES_PREFIX}/rpc_mogo.h
	${HEADER_FILES_PREFIX}/stopword.h
	${HEADER_FILES_PREFIX}/timer.h
	${HEADER_FILES_PREFIX}/timer_action.h
	${HEADER_FILES_PREFIX}/type_mogo.h
	${HEADER_FILES_PREFIX}/world.h
	${HEADER_FILES_PREFIX}/world_select.h
	${HEADER_FILES_PREFIX}/epoll_server.h
	${HEADER_FILES_PREFIX}/entity.h
	${HEADER_FILES_PREFIX}/entity_mgr.h

)

set(SOURCE_FILES_PREFIX source)
set(SOURCE_FILES 
    ${SOURCE_FILES_PREFIX}/util.cpp
    ${SOURCE_FILES_PREFIX}/balance.cpp
	${SOURCE_FILES_PREFIX}/base64.cpp
	${SOURCE_FILES_PREFIX}/bitcryto.cpp
	${SOURCE_FILES_PREFIX}/cfg_reader.cpp
	${SOURCE_FILES_PREFIX}/cjson.cpp
	${SOURCE_FILES_PREFIX}/debug.cpp
	${SOURCE_FILES_PREFIX}/defparser.cpp
	${SOURCE_FILES_PREFIX}/md5.cpp
	${SOURCE_FILES_PREFIX}/json_helper.cpp
	${SOURCE_FILES_PREFIX}/logger.cpp
	${SOURCE_FILES_PREFIX}/lua_bitset.cpp
	${SOURCE_FILES_PREFIX}/lua_mogo.cpp
	${SOURCE_FILES_PREFIX}/mailbox.cpp
	${SOURCE_FILES_PREFIX}/memory_pool.cpp
	${SOURCE_FILES_PREFIX}/net_util.cpp
	${SOURCE_FILES_PREFIX}/path_founder.cpp
	${SOURCE_FILES_PREFIX}/pluto.cpp
	${SOURCE_FILES_PREFIX}/rpc_mogo.cpp
	${SOURCE_FILES_PREFIX}/stopword.cpp
	${SOURCE_FILES_PREFIX}/timer.cpp
	${SOURCE_FILES_PREFIX}/timer_action.cpp
	${SOURCE_FILES_PREFIX}/type_mogo.cpp
	${SOURCE_FILES_PREFIX}/world.cpp
	${SOURCE_FILES_PREFIX}/epoll_server.cpp
	${SOURCE_FILES_PREFIX}/entity.cpp
	${SOURCE_FILES_PREFIX}/entity_mgr.cpp

)

source_group(header FILES ${HEADER_FILES})
source_group(source FILES ${SOURCE_FILES})

# Target
add_library(common
    ${HEADER_FILES}
    ${SOURCE_FILES}
)
