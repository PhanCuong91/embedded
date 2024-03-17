cmake_minimum_required(VERSION 3.0.0)
project(hw_interface VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(hw_interface hw_interface.c)
add_executable(zmq_api test.c)
find_library(ZMQ_LIB 
    NAMES libzmq
    PATHS "${CMAKE_INSTALL_PREFIX}/../lib/x86_64-linux-gnu")
target_link_libraries(hw_interface ${ZMQ_LIB})
target_link_libraries(zmq_api ${ZMQ_LIB})
target_include_directories(zmq_api PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources(zmq_api
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/zmq_api.c
        ${CMAKE_CURRENT_LIST_DIR}/zmq_api.h
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
