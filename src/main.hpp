#ifndef _RHAKT_ILYS_MAIN_HPP_
#define _RHAKT_ILYS_MAIN_HPP_

#ifndef NDEBUG
#if _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#endif

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <memory>
#include <unordered_map>

#define GLEW_NO_GLU
#define GLEW_STATIC
#define GLM_SWIZZLE

#define ZMQ_CPP11
#include "lib/zmq.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <lz4.h>

#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

#include "lib/spdlog/spdlog.h"




#if _MSC_VER
FILE _iob[] ={*stdin, *stdout, *stderr};
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
#endif

#include "ilys.hpp"
#include "util.hpp"


#endif