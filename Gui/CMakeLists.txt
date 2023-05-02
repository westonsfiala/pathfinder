cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(Gui)

add_definitions(-D VERSION_MAJ=${PRODUCT_VERSION_MAJ})
add_definitions(-D VERSION_MIN=${PRODUCT_VERSION_MIN})
add_definitions(-D VERSION_REV=${PRODUCT_VERSION_REV})
add_definitions(-DVERSION_STRING="${PRODUCT_VERSION_NAME}_${PRODUCT_VERSION_MAJ}.${PRODUCT_VERSION_MIN}.${PRODUCT_VERSION_REV}")

#
# Find includes in corresponding build directories
#
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#  
# Instruct CMake to run moc automatically when needed.
#
set(CMAKE_AUTOMOC ON)

set(src_CPP
	src/Main.cpp
)
    
set(src_H
)

source_group("Source Files"   FILES ${src_CPP})

add_library(${PROJECT_NAME}_lib
    ${src_CPP}
    ${src_H}
)

add_executable (${PROJECT_NAME}
    src/main.cpp

	${CMAKE_CURRENT_BINARY_DIR}/version.rc 
)

set_target_properties(${PROJECT_NAME}  PROPERTIES OUTPUT_NAME "Pathfinder_Helper")

# this block keeps the console window from appearing on Windows 
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_target_properties(${PROJECT_NAME}  PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    set_target_properties(${PROJECT_NAME}  PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# configure the version information for this executable

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/version.rc
  @ONLY)
  
#
# Include path
#   CMAKE_INCLUDE_CURRENT_DIR adds CMAKE_CURRENT_SOURCE_DIR and CMAKE_CURRENT_BINARY_DIR to include directories
#       CMAKE_CURRENT_BINARY_DIR is required for Qt generated ui_*.h 
#
set(CMAKE_INCLUDE_CURRENT_DIR ON)


target_link_libraries(${PROJECT_NAME}_lib
    PUBLIC		EncounterGenerator
	#PRIVATE    OTHER_PROJECT
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE     ${PROJECT_NAME}_lib
)

add_library(${PROJECT_NAME}PrivateHeaders INTERFACE)
target_include_directories(${PROJECT_NAME}PrivateHeaders 
    INTERFACE src
)
