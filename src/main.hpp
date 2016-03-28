#ifndef _RHAKT_ILYS_MAIN_HPP_
#define _RHAKT_ILYS_MAIN_HPP_

#if _DEBUG && _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


#include <iostream>
#include <vector>
#include <string>
#include <memory>

#define GLEW_NO_GLU
#define GLEW_STATIC
#define GLM_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <lz4.h>

#include "lib/spdlog/spdlog.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb/stb_image.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "lib/stb/stb_truetype.h"

#include "ilys.hpp"
#include "util.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

#if _MSC_VER
FILE _iob[] ={*stdin, *stdout, *stderr};
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
#endif

#endif