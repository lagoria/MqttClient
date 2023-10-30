cmake_minimum_required(VERSION 3.0)

project(MqttClient VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 11)

string(TIMESTAMP COMPILE_TIME %Y%m%d-%H%M%S)

# add mosquittopp library
find_library(MOSQUITTO_LIB mosquittopp)
if(MOSQUITTO_LIB)
	message(STATUS "mosquittopp library found: ${MOSQUITTO_LIB}")
else()
	message(FATAL_ERROR "mosquittopp library not found!")
endif()


aux_source_directory(. DIR_SRCS)


add_executable(${PROJECT_NAME} ${DIR_SRCS})

# add mosquittopp link
target_link_libraries(${PROJECT_NAME} ${MOSQUITTO_LIB})


configure_file(VersionConfig.h.in VersionConfig.h)

target_include_directories(${PROJECT_NAME} PUBLIC
							${PROJECT_BINARY_DIR}
							)
