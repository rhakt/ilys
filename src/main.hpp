#ifndef _RHAKT_ILYS_MAIN_HPP_
#define _RHAKT_ILYS_MAIN_HPP_

#ifndef NDEBUG
#if _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#endif

#include <iostream>


#define ZMQ_CPP11
#include "lib/zmq.hpp"

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