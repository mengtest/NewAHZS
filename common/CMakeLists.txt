cmake_minimum_required(VERSION 2.8)
project(common)
 
include_directories(./ ./header ../lua ../include ../cell ../base)

set(HEADER_FILES_PREFIX header)
set(HEADER_FILES
	${HEADER_FILES_PREFIX}/balance.h

)

set(SOURCE_FILES_PREFIX source)
set(SOURCE_FILES 
    ${SOURCE_FILES_PREFIX}/balance.cpp

)

source_group(header FILES ${HEADER_FILES})
source_group(source FILES ${SOURCE_FILES})

# Target
add_library(common
    ${HEADER_FILES}
    ${SOURCE_FILES}
)
