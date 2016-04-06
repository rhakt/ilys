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

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cotire/CMake)
include(cotire)
include(CMakePrintHelpers)  

if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)

if (MSVC)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2 /EHsc /MP")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /MTd /Zi")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /MT")
  
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

  if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  elseif(COMPILER_SUPPORTS_CXX1Y)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
  else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
  endif()

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -Wno-long-long -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
  
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

  if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
  elseif(COMPILER_SUPPORTS_CXX1Y)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -stdlib=libc++")
  else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
  endif()

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

endif()

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_USE_MULTITHREADED ON)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem python)
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(LZ4 REQUIRED liblz4)
find_package(glm REQUIRED glm)

include_directories(
  ${GLEW_INCLUDE_DIRS} 
  ${GLFW_INCLUDE_DIRS} 
  ${GLM_INCLUDE_DIRS} 
  ${LZ4_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR}
)

link_directories(
  ${GLEW_LIBRARY_DIRS}
  ${GLFW_LIBRARY_DIRS}
  ${LZ4_LIBRARY_DIRS}
  ${Boost_LIBRARY_DIRS}
)

if(WIN32)
  # TODO:
  include_directories(
    $ENV{ZEROMQ_DIR}/include
    $ENV{PYTHON_DIR}/include
    $ENV{SDL_DIR}/include
  )
  link_directories(
    $ENV{ZEROMQ_DIR}/lib
    $ENV{PYTHON_DIR}/libs
    $ENV{SDL_DIR}/lib
  )
endif()


set_directory_properties(PROPERTIES
  COTIRE_PREFIX_HEADER_IGNORE_PATH
    "${CMAKE_SOURCE_DIR}/src;${CMAKE_SOURCE_DIR}/src/ilys"
  COTIRE_PREFIX_HEADER_INCLUDE_PATH
    "${CMAKE_SOURCE_DIR}/src/lib"
)


# GLOB_RECURSE
file(GLOB CXX_SOURCE_FILES
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.hpp
  ${CMAKE_SOURCE_DIR}/src/ilys/*.cpp
  ${CMAKE_SOURCE_DIR}/src/ilys/*.hpp
)
add_executable(${TARGET} ${CXX_SOURCE_FILES})

if (MSVC)
   set_target_properties(${TARGET} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif ()

target_link_libraries(${TARGET} 
  ${GLEW_STATIC_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES}
  ${LZ4_LIBRARIES}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_PYTHON_LIBRARY}
  libzmq
  python34
  SDL2
  SDL2main
  SDL2_ttf
  SDL2_mixer
)

cotire(${TARGET})
