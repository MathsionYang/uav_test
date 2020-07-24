cmake_minimum_required(VERSION 3.0)
project(test)

# declaring files in your project

set ( SOURCES
      main.cpp
      baseInit.cpp
 )

set ( MOC_HEADERS
      baseInit.h
)

#set ( UIS
# src/DevInitDlg.ui
# src/GetIPDlg.ui
# src/InitializeDevDlg.ui
#)

#set ( RESOURCES
# main.qrc
#)

# Next lines needed for building all Qt projects
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories( ${CMAKE_BINARY_DIR} )
#include_directories(${PROJECT_SOURCE_DIR}/src})
include_directories("${PROJECT_SOURCE_DIR}/include")
link_directories("$ENV{HOME}/NetSDK/lib")

# Next, using precompiler, compiler and linker

# using Qt meta-system (precompiler)
QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

# compile
add_executable( ${PROJECT_NAME} ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
# or use line below instead, if you using Windows ™ Operating System.
#add_executable( PROJECT_NAME WIN32 ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )

# build it (link libraries)
target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES} -ldhnetsdk)
