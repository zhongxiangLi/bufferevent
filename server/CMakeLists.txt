project(SERVE_Reactor)
cmake_minimum_required(VERSION 3.5)





set(cmake_build_type denug)	


set(executable_output_path ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(library_output_path ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(
${CMAKE_CURRENT_SOURCE_DIR}/
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR}/LogSrc
${CMAKE_CURRENT_SOURCE_DIR}/libutils
${CMAKE_CURRENT_SOURCE_DIR}/net
${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(CMAKE_C_COMPILER "g++")

aux_source_directory(./ SRC_LIST)
aux_source_directory(include SRC_LIST)
aux_source_directory(LogSrc SRC_LIST)
aux_source_directory(libutils SRC_LIST)
aux_source_directory(net SRC_LIST)
aux_source_directory(src SRC_LIST)
add_definitions(-g -Wall )



add_executable(test_server ${SRC_LIST})
target_link_libraries(test_server pthread event)

set(executable_output_path ./bin/)
