#ifndef _RHAKT_ILYS_ILYS_COMMON_HPP_
#define _RHAKT_ILYS_ILYS_COMMON_HPP_

#include <vector>
#include <array>
#include <string>
#include <memory>
#include <utility>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <unordered_map>

#define GLEW_NO_GLU
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "../util.hpp"


namespace rhakt {
namespace ilys {
    
    using uint = unsigned int;
    using vec2 = std::array<float, 2>;
    using vec3 = std::array<float, 3>;
    using vec4 = std::array<float, 4>;
    using ivec2 = std::array<int, 2>;
    using ivec3 = std::array<int, 3>;
    using ivec4 = std::array<int, 4>;
    using uvec2 = std::array<uint, 2>;
    using uvec3 = std::array<uint, 3>;
    using uvec4 = std::array<uint, 4>;
    using colot_t = vec4;
    using icolor_t = std::array<unsigned char, 4>;
    

} // end of namespace ilys
} // end of namespace rhakt


#endif