cmake_minimum_required(VERSION 2.8.9)
project(server)

# Add header file include directories
include_directories(./ ./header ../ ../websocketpp ../wepoll/include ../serverlib/header)
if(MSVC)
	link_directories("../include/mysql/")
endif()

# Target
add_executable(server
    main.cpp
)

if(MSVC)
	target_link_libraries(server tinyxml wepoll hiredis libmysql googleTest)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
else()

endif()
target_link_libraries(server tinyxml hiredis serverlib)

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pthread -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -pthread -std=c++11")
endif()
