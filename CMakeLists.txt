cmake_minimum_required(VERSION 3.0.2)

project(qtlc3project)

set( CMAKE_VERBOSE_MAKEFILE on )

set(CMAKE_CXX_FLAGS "-fPIC")
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(AUTOMOC_MOC_OPTIONS "-Iinc")

file(COPY help DESTINATION .)
file(COPY lc3os.obj DESTINATION .)

find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
find_package(PythonInterp REQUIRED)

include_directories(${QT_INCLUDES}) 
find_package(Boost REQUIRED)
find_package(Boost COMPONENTS python REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/pylc3/inc)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
# find_package(Qt5Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Widgets_LIBRARIES} ${Qt5Core_INCLUDE_DIRS} ${Qt5Core_LIBRARIES})

# file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp pylc3/src/*.cpp)
# file(GLOB SOURCES src/*.cpp inc/*.h pylc3/src/*.cpp pylc3/inc/*.hpp)
#file(GLOB SOURCES src/*.cpp pylc3/src/*.cpp)
file(GLOB SOURCES src/*.cpp)
file(GLOB UI_FILES src/*.ui)

# file(GLOB PYLC3SOURCES pylc3/src/*.cpp)

qt5_wrap_cpp(qt5_src inc/helpsystem.h inc/lc3console.h inc/mainwindow.h inc/qconsole.h)
qt5_wrap_ui(qt5_ui ${UI_FILES})

message(STATUS "SOURCES: " ${SOURCES})
add_subdirectory(pylc3)


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
#if(WIN32)
    add_executable(qtlc3 WIN32 ${SOURCES} ${qt5_src} ${qt5_ui} qdarkstyle/style.qrc)
#else(WIN32)
#    add_executable(qltc3 ${SOURCES} ${qt5_src} ${qt5_ui} qdarkstyle/style.qrc) 
#endif(WIN32)

add_definitions(-DPREFIX="${DESTDIR}")

target_link_libraries(qtlc3 libpylc3)
target_link_libraries(qtlc3 ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

# Use the Widgets module from Qt 5.
target_link_libraries(qtlc3 Qt5::Widgets)
#target_link_libraries(qtlc3 Qt5::Gui)
#target_link_libraries(qtlc3 Qt5::Core)
#target_link_libraries(qtlc3 ${QT5_LIBRARIES})
# target_compile_definitions(qtlc3 PRIVATE PREFIX="${DESTDIR}")

#target_include_directories(qtlc3 INTERFACE
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
#  $<INSTALL_INTERFACE:include/pylc3>)
install(TARGETS qtlc3 DESTINATION /usr/share/qtlc3)
install(FILES lc3os.obj  DESTINATION /usr/share/qtlc3)
install(DIRECTORY help DESTINATION /usr/share/qtlc3)
