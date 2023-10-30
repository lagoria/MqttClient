cmake_minimum_required(VERSION 3.0)

project(MqttClient VERSION 1.0.1)

# 使用C++11标准
set(CMAKE_CXX_STANDARD 11)
# 时间戳
string(TIMESTAMP COMPILE_TIME %Y%m%d-%H%M%S)
# 宏定义 USE_THE_CMAKE
add_definitions(-D USE_THE_CMAKE)

# add mosquittopp library
find_library(MOSQUITTO_LIB mosquittopp)
if(MOSQUITTO_LIB)
	message(STATUS "mosquittopp library found: ${MOSQUITTO_LIB}")
else()
	message(FATAL_ERROR "mosquittopp library not found!")
endif()

# 添加所有当前目录的源文件
aux_source_directory(. DIR_SRCS)


add_executable(${PROJECT_NAME} ${DIR_SRCS})

# add mosquittopp link
target_link_libraries(${PROJECT_NAME} ${MOSQUITTO_LIB})

# 版本配置文件
configure_file(VersionConfig.h.in VersionConfig.h)
# 包含build/目录下的头文件
target_include_directories(${PROJECT_NAME} PUBLIC
							${PROJECT_BINARY_DIR}
							)
