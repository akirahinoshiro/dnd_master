PROJECT(minimal)
cmake_minimum_required(VERSION 3.1)
add_definitions(-DUSE_QT)

set (CMAKE_CXX_STANDARD 17)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror -O3 -march=native -ffast-math -mtune=skylake-avx512 -masm=intel")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror -O3 -march=native -ffast-math -mtune=intel -mfpmath=both -masm=intel -malign-data=cacheline")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
    set(BOOST_ROOT "C://boost//boost_1_72_0")
    set(BOOST_INCLUDE_DIR "${BOOST_ROOT}")
    set(BOOST_LIBRARY_DIR "${BOOST_ROOT}//lib64-msvc-14.1")
    set (CMAKE_PREFIX_PATH "C://Qt//5.14.1//msvc2017_64")
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

#use pthreads if unix or unix-alike (linux)
if(UNIX)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
endif()

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${BOOST_INCLUDE_DIR})
link_directories(${BOOST_LIBRARY_DIR})

FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
FILE(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
FILE(GLOB UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")
FILE(GLOB RC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc")

QT5_ADD_RESOURCES(ENTITY_DEBUGGER_RC_SRCS ${RC_FILES} )
QT5_WRAP_UI( ENTITY_DEBUGGER_UI_HDRS ${UI_FILES})

ADD_EXECUTABLE( minimal 
				${CPP_FILES}
				${HEADER_FILES} 
				${ENTITY_DEBUGGER_RC_SRCS} 
				${ENTITY_DEBUGGER_UI_HDRS} 
				)

SET_TARGET_PROPERTIES(minimal PROPERTIES DEBUG_POSTFIX _d)

target_link_libraries( minimal ${BOOST_LIBRARIES} Qt::Widgets Qt::Core Qt::Xml)
if (UNIX)
	target_link_libraries(minimal Threads::Threads)
endif ()

INSTALL(TARGETS minimal
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
