cmake_minimum_required (VERSION 3.20)
#--------------------------------------------------------------------------------------------------
# variables
set(PROJECT_NAME RtspClient)
file(GLOB SOURCES CONFIGURE_DEPENDS
    "*.h"
    "*.cpp"
    )
#--------------------------------------------------------------------------------------------------
# project
project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})
#--------------------------------------------------------------------------------------------------
# builds
add_library(${PROJECT_NAME} ${SOURCES})
#--------------------------------------------------------------------------------------------------
# link libraries
target_link_libraries(${PROJECT_NAME} QueueFrame)
target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR}/QueueFrame)
if(CONAN_PKG)
    message("Create with Conan")
    #
    # OpenCV
    find_package(OpenCV CONFIG REQUIRED)
    target_link_libraries(${PROJECT_NAME} opencv::opencv)
    #
else()
    message("Create with vcpkg or nativ ")
    # OpenCV
    #
    find_package(OpenCV REQUIRED)
    #include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
    target_include_directories(${PROJECT_NAME} PUBLIC 
        ${LIB_INCLUDE_DIR}
        ${OpenCV_INCLUDE_DIRS}
        )
    #
endif()
#--------------------------------------------------------------------------------------------------