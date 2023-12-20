cmake_minimum_required(VERSION 3.12)
#project(test_app)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# Compile WPILIB
set(USE_SYSTEM_EIGEN OFF)
set(USE_SYSTEM_FMTLIB OFF)
set(WITH_JAVA OFF)
set(WITH_CSCORE OFF)
set(WITH_NTCORE ON)
set(WITH_WPIMATH OFF)
set(WITH_WPILIB OFF)
set(WITH_TESTS OFF)
set(WITH_GUI OFF)
set(WITH_SIMULATION_MODULES OFF)

if(NOT DEFINED ENV{WPI_BUILT})
	set(ENV{WPI_BUILT} ON)
	add_subdirectory(allwpilib)
endif()

#add_executable(test_app test.cpp)
#target_include_directories(test_app PRIVATE "$<TARGET_PROPERTY:ntcore,INTERFACE_INCLUDE_DIRECTORIES>")
#target_link_libraries(test_app PRIVATE ntcore)
