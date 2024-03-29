﻿cmake_minimum_required(VERSION 3.5.0)
PROJECT(dnd_master)
set(Callgrind OFF)

# add_definitions(-DUSE_QT)
set(CMAKE_CXX_STANDARD 23)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using Clang or GCC
  if(Callgrind STREQUAL "ON")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror -O2")
  else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment -O2")
  endif()

# using Intel C++
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
# using Visual Studio C++
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(BOOST_ROOT "C://boost//boost_1_72_0")
  set(BOOST_INCLUDE_DIR "${BOOST_ROOT}")
  set(BOOST_LIBRARY_DIR "${BOOST_ROOT}//lib64-msvc-14.1")
  set(CMAKE_PREFIX_PATH "C://Qt//5.14.1//msvc2017_64")

  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
endif()

# use pthreads if unix or unix-alike (linux)
if(UNIX)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
endif()

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)

# find_package(Qt5Core REQUIRED)
# find_package(Qt5Xml REQUIRED)
# find_package(Boost COMPONENTS system REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB MAIN "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
FILE(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
FILE(GLOB QT_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/qt/*.h")
FILE(GLOB QT_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/qt/*.cpp")
FILE(GLOB QT_UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/qt/*.ui")
FILE(GLOB QT_RC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/qt/*.qrc")
list(REMOVE_ITEM CPP_FILES ${MAIN})
QT5_ADD_RESOURCES(ENTITY_DEBUGGER_RC_SRCS ${QT_RC_FILES})
QT5_WRAP_UI(ENTITY_DEBUGGER_UI_HDRS ${QT_UI_FILES})

ADD_EXECUTABLE(${PROJECT_NAME}
  ${MAIN}
  ${CPP_FILES}
  ${HEADER_FILES}
  ${QT_CPP_FILES}
  ${QT_HEADER_FILES}
  ${ENTITY_DEBUGGER_RC_SRCS}
  ${ENTITY_DEBUGGER_UI_HDRS}
)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)

# target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES} Qt::Widgets Qt::Core Qt::Xml)
target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES} Qt::Widgets)

if(UNIX)
  target_link_libraries(${PROJECT_NAME} Threads::Threads)
endif()

INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
# INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/tests_qt/CMakeLists.txt")
