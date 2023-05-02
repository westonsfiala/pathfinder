cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(EncounterGenerator)

set(src_CPP
    src/Encounter.cpp
    src/EncounterGenerator.cpp
	src/FileHelper.cpp
    src/FilledEncounter.cpp
	src/GeneratorUtilities.cpp
	src/Monster.cpp
	src/MonsterList.cpp
	src/Party.cpp
)
    
set(src_H
	include/Encounter.h
	include/EncounterGenerator.h
	include/FileHelper.h
	include/FilledEncounter.h
	include/GeneratorUtilities.h
	include/Monster.h
	include/MonsterList.h
	include/Party.h
)

add_library(${PROJECT_NAME} STATIC
    ${src_CPP}
    ${src_H}
	EncounterGenerator.natvis
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC nlohmann_json::nlohmann_json
)

target_include_directories(${PROJECT_NAME}
	PUBLIC include
	PRIVATE src
)

add_library(${PROJECT_NAME}PrivateHeaders INTERFACE)
target_include_directories(${PROJECT_NAME}PrivateHeaders 
    INTERFACE src
)