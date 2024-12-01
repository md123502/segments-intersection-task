cmake_minimum_required(VERSION 3.18)

set(LIBRARY_OUTPUT_NAME vecseg)

set(SRCS Vector3D.cpp Segment3D.cpp)

add_library(${LIBRARY_OUTPUT_NAME} ${SRCS})

