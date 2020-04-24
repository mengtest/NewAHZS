cmake_minimum_required(VERSION 2.8)

 
# 必要的变量。方便后面引用代码位置。
project(wepoll)
SET(PROJECT_ROOT_PATH ".")

include_directories(
    "${PROJECT_SOURCE_DIR}"
)
 
add_library (wepoll
	${PROJECT_ROOT_PATH}/src/wepoll.c
)