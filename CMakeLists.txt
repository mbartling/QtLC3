cmake_minimum_required(VERSION 3.1.3)

project(qtlc3project)

set( CMAKE_VERBOSE_MAKEFILE on )

set(CMAKE_CXX_FLAGS "-fPIC")
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
# find_package(Qt5Widgets REQUIRED)

find_package(PythonLibs 2.7 REQUIRED)
include_directories(${QT_INCLUDES}) 
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(Boost)
find_package(Boost COMPONENTS python REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/pylc3/inc)


include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Widgets_LIBRARIES} ${Qt5Core_INCLUDE_DIRS} ${Qt5Core_LIBRARIES})

# file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp pylc3/src/*.cpp)
# file(GLOB SOURCES src/*.cpp inc/*.h pylc3/src/*.cpp pylc3/inc/*.hpp)
set(SOURCES ${SOURCES} src/qconsole.cpp src/mainwindow.cpp src/helpsystem.cpp src/lc3console.cpp src/main.cpp pylc3/src/simulator.cpp)
# file(GLOB PYLC3SOURCES pylc3/src/*.cpp)

message(STATUS "SOURCES: " ${SOURCES})
# add_subdirectory(pylc3)

add_executable(qltc3 qdarkstyle/style.qrc ${SOURCES})

# target_compile_features(qtlc3 PRIVATE cxx_range_for)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
# Tell CMake to create the qltc3 executable
add_executable(qtlc3 WIN32 ${SOURCES} qdarkstyle/style.qrc)

# Use the Widgets module from Qt 5.
target_link_libraries(qtlc3 Qt5::Widgets
  ${Boost_LIBRARIES}
  ${PYTHON_LIBRARIES})
# target_link_libraries(qtlc3 Qt5::Gui)
# target_link_libraries(qtlc3 Qt5::Core)
# target_link_libraries(qtlc3 ${Qt5Widgets_LIBRARIES})
# target_compile_definitions(qtlc3 PRIVATE PREFIX="${DESTDIR}")
add_definitions(-DPREFIX="${DESTDIR}")

# target_link_libraries(qtlc3 pylc3)

# target_include_directories(qtlc3 INTERFACE
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
#   $<INSTALL_INTERFACE:include/pylc3>)
