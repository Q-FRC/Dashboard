cmake_minimum_required(VERSION 3.5)

enable_testing()

project(Tests LANGUAGES CXX)

set(CMAKE_AUTOUIC_SEARCH_PATHS "../lib/ui")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets MultimediaWidgets Charts Test Gui)
find_package(ntcore)
find_package(Protobuf)

add_subdirectory("../lib" ${CMAKE_CURRENT_BINARY_DIR}/lib)

macro(AddTest _name _src)
    add_executable(${_name} ${_src})

    target_link_libraries(${_name} PRIVATE QFRCDashboardLib Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::MultimediaWidgets Qt${QT_VERSION_MAJOR}::Charts ntcore BuildConfig Qt${QT_VERSION_MAJOR}::Test)

    target_include_directories(${_name} PRIVATE "$<TARGET_PROPERTY:ntcore,INTERFACE_INCLUDE_DIRECTORIES>")
    target_include_directories(${_name} PRIVATE ../lib/ui/)
    target_include_directories(${_name} PRIVATE ../lib/include)
    target_include_directories(${_name} PRIVATE ${_Dashboard_AUTOGEN}/include)
    target_include_directories(${_name} PRIVATE ../lib/)

    message(STATUS ${_Dashboard_AUTOGEN}/include)

    add_test(NAME ${_name} COMMAND ${_name})
endmacro()

AddTest(SaveLoad tst_saveload.cpp)
