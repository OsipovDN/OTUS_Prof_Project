cmake_minimum_required (VERSION 3.20)

option(CONAN_PKG "Build using a batch manager" OFF)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "Create separate directory for build.")
endif()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
endif()

set(PROJECT_VESRION 0.0.1)
set(LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")

file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

project(trafficRecorder VERSION ${PROJECT_VESRION})
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

if(CONAN_PKG)
    message("Create with Conan")
    find_package(Boost CONFIG REQUIRED)
    find_package(OpenCV CONFIG REQUIRED)
    find_package(GTest CONFIG REQUIRED)

    target_link_libraries(${PROJECT_NAME} boost::boost)
    target_link_libraries(${PROJECT_NAME} opencv::opencv)
    target_link_libraries(${PROJECT_NAME} GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
else()
    message("Create with system libs")
    find_package (Boost 1.83 REQUIRED)
    if(Boost_FOUND)
        target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
        target_link_libraries (${PROJECT_NAME} PRIVATE libasync ${Boost_LIBRARIES})
    endif()
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

    target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIR})

    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GTEST_BOTH_LIBRARIES})
endif()



if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /EHsc
        /W4
        /WX
    )

endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

#set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(trafficRecorder_gtest trafficRecorder_gtest)




