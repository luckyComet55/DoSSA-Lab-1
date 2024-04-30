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
include_directories(libs/headers)
include_directories(UnitTest/HeaderFiles)

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
        Lab1/HeaderFiles/CEcoLab1.h
        Lab1/HeaderFiles/CEcoLab1Factory.h
        Lab1/SourceFiles/CEcoLab1Factory.c
        Lab1/SharedFiles/IdEcoLab1.h
        Lab1/SharedFiles/IEcoLab1.h

        Lab1/HeaderFiles/CEcoLab1ConnectionPoint.h
        Lab1/HeaderFiles/CEcoLab1EnumConnectionPoints.h
        Lab1/HeaderFiles/CEcoLab1EnumConnections.h

        Lab1/SharedFiles/IEcoConnectionPoint.h
        Lab1/SharedFiles/IEcoConnectionPointContainer.h
        Lab1/SharedFiles/IEcoEnumConnectionPoints.h
        Lab1/SharedFiles/IEcoEnumConnections.h
        Lab1/SharedFiles/IEcoLab1Events.h

        Lab1/SourceFiles/CEcoLab1ConnectionPoint.c
        Lab1/SourceFiles/CEcoLab1EnumConnectionPoints.c
        Lab1/SourceFiles/CEcoLab1EnumConnections.c

        ${ECO_CALC_LIB}
)

add_executable(
        Lab3
        UnitTest/SourceFiles/EcoLab3.c
        UnitTest/HeaderFiles/CEcoLab1Sink.h
        UnitTest/SourceFiles/CEcoLab1Sink.c
)
add_custom_command(TARGET Lab3 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/libs/dll"
        $<TARGET_FILE_DIR:Lab3>
)

target_link_libraries(
        Lab3
        1F5DF16EE1BF43B999A434ED38FE8F3C
        ${ECO_FRAMEWORK_DOT_LIB}
)