cmake_minimum_required(VERSION 3.0.0)
project(trace VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(example example.c barectf.c barectf-platform-linux-fs.c)
# add_subdirectory(./zeromq)
find_library(ZMQ_LIB 
    NAMES libzmq
    PATHS "${CMAKE_INSTALL_PREFIX}/../lib/x86_64-linux-gnu")
target_link_libraries(example ${ZMQ_LIB})
target_include_directories(example PUBLIC ${CMAKE_CURRENT_LIST_DIR}/zeromq)
target_sources(example
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/zeromq/zmq_api.c
        ${CMAKE_CURRENT_LIST_DIR}/zeromq/zmq_api.h
)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
