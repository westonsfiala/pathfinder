# Minimum version required
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14) 

#=============================================================
# Setup product name, version, etc.
#=============================================================

#
# Get build-generated versions file, if it exists
#
include (CMake.Version.txt OPTIONAL)

# local builds will have a 1.0.0 version
if(NOT DEFINED PRODUCT_VERSION_MAJ)
    set (PRODUCT_VERSION_NAME  "DEV")
    set (PRODUCT_VERSION_MAJ   "1")
    set (PRODUCT_VERSION_MIN   "0")
    set (PRODUCT_VERSION_REV   "0")
    set (PRODUCT_VERSION_PATCH "0")
endif()

set(PRODUCT_VERSION ${PRODUCT_VERSION_NAME}_${PRODUCT_VERSION_MAJ}.${PRODUCT_VERSION_MIN}.${PRODUCT_VERSION_REV}.${PRODUCT_VERSION_PATCH}) 

set(PLATFORM_NAME                 "Pathfinder Helper")
set(COMPANY_NAME                  "Weston")
set(COMPANY_NAME_FULL             "Weston Fiala")
set(COPYRIGHT_STRING              "Copyright ${COMPANY_NAME_FULL} 2018-2023")

# PRODUCT_DESCRIPTION is the name displayed in the 'Open With' shortcut and in the .exe file properties Description
set(PRODUCT_DESCRIPTION           "${COMPANY_NAME} ${PLATFORM_NAME}")

string(TIMESTAMP BUILD_TIMESTAMP %Y%m%d_%H%M%S)

#
#  Define project name
#
project (Pathfinder_Helper)

# Set the output directories
# See:  https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#output-artifacts

# Runtime contains
#     [WIN/LIN] executable files
#     [WIN    ] DLLs created with add_library(SHARED)
# Library contains
#     [WIN    ] DLLs created with add_library(MODULE)
#     [    LIN] .so files created with add_library(SHARED) or add_library(MODULE)
# Archive contains
#     [WIN/LIN] static library files (.lib/.a) created with add_library(STATIC)
#     [WIN    ] import library files (.lib) for DLLs created with add_library(SHARED)
#     [WIN    ] import library files (.lib) for executables created with ENABLE_EXPORTS

# make sure we have the correct output directories in all configurations
if (WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    # debug
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug/lib)
    # release
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/lib)

else()
    # On Linux, we don't want Debug and Release directories at all.
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif (WIN32)



#
# Turn on the ability to create folders to organize projects (.vcproj)
#
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Put the automatic Qt MOC projects into a separate folder in the VS solution
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER "autogen")

#=============================================================
# Special Windows compiler options
#=============================================================
if (WIN32)

	# this fixes wsprintf casting problems
    add_definitions(-DUNICODE)
    
    # This prevents boost 1.66 from complaining about Visual Studio 15.5 and later.
    # Normally this should prompt us to update to a newer boost, but as of 3/29/18 1.66 is the latest.
    # add_definitions(-DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE)
	
	# Prevents visual studio from complaining about getenv and other functions which
	# are part of the standard, but which visual studio defines as deprecated and
	# suggests a non-portable alternative which will not work on linux
    #add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    #add_definitions(-D_SCL_SECURE_NO_WARNINGS)

	# Set compiler flags and options.
	# Set the Visual Studio warning level to 4
	# Set Multi-processor compilation ON
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /MP")

	# Suppress  '<function> marked as __forceinline not inlined'; most __forceinlines are in Qt headers
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4714")
	#
	# Hide specific compiler warnings
	#
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4127") # conditional expression is constant 

    #
    # create debug symbols for Release builds
    #     /OPT:ICF - turns on COMDAT folding (makes binaries smaller)
    #     /OPT:REF - include only used references
    #
    set(CMAKE_CXX_FLAGS_RELEASE           "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE    "${CMAKE_EXE_LINKER_FLAGS_RELEASE}    /DEBUG /OPT:REF /OPT:ICF")
    
else()

    # Enable "all" warnings
    # For more warnings that are less likely to be useful, add -Wextra
    # disable silly warnings as well (-Wno-comment disables warnings about nested comments)
    # -Werror turns all warnings into errors
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-comment -Werror")
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
    set (CMAKE_POSITION_INDEPENDENT_CODE ON)

    # Tell executables to look for .so files in the lib directory next to the executable
    set (CMAKE_INSTALL_RPATH "\$ORIGIN/lib")
    # CMake uses different rpath for the build tree and for installed.
    # Since we don't use the "install" target, we want to use the installed rpath in the build tree.
    set (CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    # I don't entirely understand what these are needed for.
    set (CMAKE_SKIP_BUILD_RPATH TRUE)
    set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


endif(WIN32)

#
# Put a "d" after out debug target names 
#
set (CMAKE_DEBUG_POSTFIX "d")

#
# We want testing (ctest)
#
enable_testing()
set(TEST_RESULT_DIR ${CMAKE_BINARY_DIR}/TestResults)


# Traditional cmake (release or debug)
set(CURRENT_CONFIGURATION_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PATHFINDER_OUTPUT_DIR ${CURRENT_CONFIGURATION_OUTPUT_DIRECTORY})
set(CMAKE_INSTALL_PREFIX ${PATHFINDER_OUTPUT_DIR})

#
# Override Boost library filter 
#
# other boost subsets: _system|_iostreams|_serialization|_zlib|_date_time|_regex
#define_boost_subset("BoostSubset" "(_filesystem|_program_options|_system)")

# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")

#
# Application targets
#
add_subdirectory(json)
add_subdirectory(EncounterGenerator)
add_subdirectory(Gui)

#=============================================================
# Organize projects nicely within the IDE (Visual Studio)
#=============================================================

set(MAIN_GUI_FOLDER "Frontend") 
set_property(TARGET Gui     PROPERTY FOLDER ${MAIN_GUI_FOLDER})
set_property(TARGET Gui_lib PROPERTY FOLDER ${MAIN_GUI_FOLDER})

set(BACKEND_FOLDER "Backend") 
set_property(TARGET EncounterGenerator PROPERTY FOLDER ${BACKEND_FOLDER})

#
# Set the default start-up project (for Visual Studio)
#
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Gui)
