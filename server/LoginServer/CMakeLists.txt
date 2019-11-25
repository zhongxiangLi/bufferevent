project(LOGIN_SERVER)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
set(library_output_path ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protobuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but cant be found")
endif()

set(PROTO_FILES ../protobuf/test.proto)
set(cmake_build_type denug)	

AUX_SOURCE_DIRECTORY(src LOGIN_SRC)
AUX_SOURCE_DIRECTORY(../net/include LOGIN_SRC)

INCLUDE_DIRECTORIES(../net/include)
INCLUDE_DIRECTORIES(../libutils)
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${PROTO_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

LINK_DIRECTORIES(../libs/)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

set(CMAKE_C_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g  -ffunction-sections -O0 -D_GLIBCXX_USE_CXX11_ABI=0 ")


add_executable(loginserver ${LOGIN_SRC}  ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(loginserver net_static pthread event protobuf ${PROTOBUF_LIBRARIES})

set(executable_output_path ../bin/)
