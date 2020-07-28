cmake_minimum_required(VERSION 3.0)
project(uav_test)
add_definitions(-std=c++11 -Wall -g)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
set ( SOURCES
 src/main.cpp
 src/dahua_dev.cpp )

set ( MOC_HEADERS
 include/dhconfigsdk.h
 include/dhnetsdk.h
 include/dahua_dev.h
)

# set(OpenCV_DIR "/opt/ros/kinetic/share/OpenCV-3.3.1-dev")
find_package(OpenCV REQUIRED)

include_directories( ${PROJECT_SOURCE_DIR}/include
                     ${CMAKE_BINARY_DIR}
                     ${PROJECT_SOURCE_DIR}/3rdparty/libav_Mat/include
                     ${OpenCV_INCLUDE_DIRS})
link_directories("$ENV{HOME}/NetSDK/lib"
        ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libav_Mat/build)

# compile
add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries( ${PROJECT_NAME}
        -ldhnetsdk
        ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libav_Mat/build/liblibav.so
        ${OpenCV_LIBS}
        ${CMAKE_THREAD_LIBS_INIT})
