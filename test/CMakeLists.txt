cmake_minimum_required (VERSION 3.14)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

project (trafficRecorder_gtest)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})




