cmake_minimum_required (VERSION 3.20)
 
#--------------------------------------------------------------------------------------------------
# options
option(CONAN_PKG "Build using a batch manager" OFF)

#--------------------------------------------------------------------------------------------------
# variables
set(PROJECT_VESRION 0.0.1)
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(PROJECT_NAME  trafficRecorder)
set(TEST_NAME UnitTest)

#file(GLOB HEADERS CONFIGURE_DEPENDS
    #"${SRC_DIR}/RtspClient/*.h"
#    )
file(GLOB SOURCES CONFIGURE_DEPENDS
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/RtspClient/*.cpp"
    "${SRC_DIR}/QueueFrame/*.cpp"
    "${SRC_DIR}/ObjectSearcher/*.cpp"
    )

#--------------------------------------------------------------------------------------------------
# project
project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})

if (MSVC)
	# enable VS-Solution filters support
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif (MSVC)
#--------------------------------------------------------------------------------------------------
# builds
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "Create separate directory for build.")
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
endif()

add_executable(${PROJECT_NAME}
    ${SOURCES}
    )
add_executable(${TEST_NAME}
    ${TEST_DIR}/trafficRecorder_gtest.cpp
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
 )

 set_target_properties(${TEST_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
 )

 target_include_directories(${PROJECT_NAME} PUBLIC
    ${SRC_DIR}
    ${SRC_DIR}/QueueFrame
    ${SRC_DIR}/RtspClient
    ${SRC_DIR}/ObjectSearcher
    )
 
#--------------------------------------------------------------------------------------------------
# link libraries
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 OLD)
endif()
if(CONAN_PKG)
    message("Create with Conan")
    find_package(Boost 1.74 CONFIG REQUIRED)
    find_package(OpenCV CONFIG REQUIRED)
    find_package(GTest CONFIG REQUIRED)

    target_link_libraries(${PROJECT_NAME} boost::boost)
    target_link_libraries(${PROJECT_NAME} opencv::opencv)
    target_link_libraries(${PROJECT_NAME} GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
else()
    message("Create with vcpkg or nativ ")
    # Boost
    #
    find_package (Boost 1.74 REQUIRED)
    if(Boost_FOUND)
    	target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
    	target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
     endif(Boost_FOUND)
     #
     # OpenCV
     #
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
    target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIR})
    #
    # GTest
    #
    find_package(GTest REQUIRED)
    target_include_directories(${TEST_NAME} 
	    PRIVATE
	    ${SRC_DIR}
        ${TEST_DIR}
	    ${GTEST_INCLUDE_DIR}
	    #${GTEST_LIBRARY}
 	    )
    target_link_libraries(${TEST_NAME} PRIVATE ${GTEST_BOTH_LIBRARIES})
endif()

#--------------------------------------------------------------------------------------------------
# compiler settings

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
    target_compile_options(${TEST_NAME} PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /EHsc
        #/W4
        /WX
    )
    target_compile_options(${TEST_NAME} PRIVATE
        /EHsc
        #/W4
        /WX
    )
endif()

#--------------------------------------------------------------------------------------------------
# deb pkg
if (UNIX)
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

	set(CPACK_GENERATOR DEB)

	set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
	set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
	set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
	#set(CPACK_PACKAGE_CONTACT example@example.com)

	include(CPack)
endif (UNIX)

#--------------------------------------------------------------------------------------------------
# testing
enable_testing()
add_test(trafficRecorder_gtest trafficRecorder_gtest)

#include(GoogleTest)
#gtest_discover_tests(${TEST_NAME})



