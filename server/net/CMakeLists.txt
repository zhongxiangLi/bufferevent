project(net)
cmake_minimum_required(VERSION 3.5)

set(LIBRARY_OUTPUT_PATH ../libs)

AUX_SOURCE_DIRECTORY(src net_src)
AUX_SOURCE_DIRECTORY(../libutils libutils_src)


INCLUDE_DIRECTORIES(../libutils)
INCLUDE_DIRECTORIES(include)

ADD_DEFINITIONS(-g -Wall)

SET(cmake_build_type Debug)

ADD_LIBRARY(net_static STATIC ${net_src} ${libutils_src})

TARGET_LINK_LIBRARIES(net_static event event_core event_pthreads)

