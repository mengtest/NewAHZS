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

)

source_group(header FILES ${HEADER_FILES})
source_group(source FILES ${SOURCE_FILES})

# Target
add_library(common
    ${HEADER_FILES}
    ${SOURCE_FILES}
)
