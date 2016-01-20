cmake_minimum_required(VERSION 2.8)

project(ilys CXX)

ENABLE_LANGUAGE(C)

set(TARGET ${PROJECT_NAME})

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif()

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall /W2 /EHsc /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -Wall -Wno-long-long -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

find_package(PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLFW glfw3)
if (GLFW_FOUND)
  pkg_search_module(GLFW REQUIRED libglfw)
endif()

include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS} ${GLFW_LIBRARY_DIRS})

file(GLOB CXX_SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(${TARGET} ${CXX_SOURCE_FILES})

if (MSVC)
   set_target_properties(${TARGET} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif ()

target_link_libraries(${TARGET} ${GLEW_LIBRARIES} ${GLFW_STATIC_LIBRARIES})
