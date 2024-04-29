cmake_minimum_required(VERSION 3.26)
project(Lab1 C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS "/TC /Gz")
set(CMAKE_SHARED_LINKER_FLAGS "/DYNAMICBASE")
set(CMAKE_EXE_LINKER_FLAGS "/DYNAMICBASE")

add_definitions(-DECO_WINDOWS)
add_definitions(-D_DEBUG)
add_definitions(-DECO_DLL)
add_definitions(-DUGUID_UTILITY)
add_definitions(-DECO_WIN32)
add_definitions(-D_WIN32)
add_definitions(-D_WINDOWS)
add_definitions(-D_CONSOLE)

include_directories(Lab1/HeaderFiles)
include_directories(Lab1/SharedFiles)
include_directories(Lab2/HeaderFiles)
include_directories(Lab2/SharedFiles)
include_directories(libs/headers)

set(ECO_FRAMEWORK_DOT_LIB
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000042757331.lib
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/BuildFiles/Windows/x86/StaticRelease/0000000000000000000000004D656D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000046534D31.lib
        $ENV{ECO_FRAMEWORK}/Eco.System1/BuildFiles/Windows/x86/StaticRelease/00000000000000000000000000000100.lib
)


include_directories(
        $ENV{ECO_FRAMEWORK}/Eco.List1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.Core1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.InterfaceBus1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.System1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.MemoryManager1/SharedFiles
        $ENV{ECO_FRAMEWORK}/Eco.FileSystemManagement1/SharedFiles
)

set(ECO_CALC_LIB
        libs/headers/IEcoCalculatorX.h
        libs/headers/IEcoCalculatorY.h
        libs/headers/IdEcoCalculatorA.h
        libs/headers/IdEcoCalculatorB.h
        libs/headers/IdEcoCalculatorD.h
        libs/headers/IdEcoCalculatorE.h
)

add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3C
        SHARED
        Lab1/SourceFiles/CEcoLab1.c
        Lab1/SourceFiles/CEcoLab1Factory.c
        Lab1/SourceFiles/CEcoLab1ConnectionPoint.c
        Lab1/SourceFiles/CEcoLab1EnumConnectionPoints.c
        Lab1/SourceFiles/CEcoLab1EnumConnections.c
        Lab1/SharedFiles/IdEcoLab1.h
        Lab1/SharedFiles/IEcoLab1.h
        Lab1/SharedFiles/IEcoConnectionPoint.h
        Lab1/SharedFiles/IEcoConnectionPointContainer.h
        Lab1/SharedFiles/IEcoEnumConnectionPoint.h
        Lab1/SharedFiles/IEcoEnumConnections.h
        Lab1/SharedFiles/IEcoLab1Events.h
        Lab1/HeaderFiles/CEcoLab1.h
        Lab1/HeaderFiles/CEcoLab1Factory.h
        Lab1/HeaderFiles/CEcoLab1ConnectionPoint.h
        Lab1/HeaderFiles/CEcoLab1EnumConnectionPoints.h
        Lab1/HeaderFiles/CEcoLab1EnumConnections.h
        Lab1/HeaderFiles/CEcoLab1Sink.h
        Lab1/SourceFiles/CEcoLab1Sink.c
        ${ECO_CALC_LIB}
)

add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3A
        SHARED
        Lab1/SourceFiles/CEcoLab1.c
        Lab1/SourceFiles/CEcoLab1Factory.c
        Lab1/SharedFiles/IdEcoLab1.h
        Lab1/SharedFiles/IEcoLab1.h
        Lab1/HeaderFiles/CEcoLab1.h
        Lab1/HeaderFiles/CEcoLab1Factory.h
        ${ECO_CALC_LIB}
)

add_library(
        1F5DF16EE1BF43B999A434ED38FE8F3B
        SHARED
        Lab2/SourceFiles/CEcoLab2.c
        Lab2/SourceFiles/CEcoLab2Factory.c
        Lab2/SharedFiles/IdEcoLab2.h
        Lab2/HeaderFiles/CEcoLab2.h
        Lab2/HeaderFiles/CEcoLab2Factory.h
)

add_executable(
        Lab3
        UnitTest/EcoLab3.c
)

add_executable(
        Lab1
        UnitTest/EcoLab1.c
)

add_executable(
        Lab2
        UnitTest/EcoLab2.c
        ${ECO_CALC_LIB}
)

add_custom_command(TARGET Lab2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/libs/dll"
        $<TARGET_FILE_DIR:Lab2>
)

target_link_libraries(
        Lab1
        1F5DF16EE1BF43B999A434ED38FE8F3A
        ${ECO_FRAMEWORK_DOT_LIB}
)
target_link_libraries(
        Lab2
        1F5DF16EE1BF43B999A434ED38FE8F3B
        1F5DF16EE1BF43B999A434ED38FE8F3A
        ${ECO_FRAMEWORK_DOT_LIB}
)
target_link_libraries(
        Lab3
        1F5DF16EE1BF43B999A434ED38FE8F3C
        ${ECO_FRAMEWORK_DOT_LIB}
)