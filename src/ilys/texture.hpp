#ifndef _RHAKT_ILYS_ILYS_TEXTURE_HPP_
#define _RHAKT_ILYS_ILYS_TEXTURE_HPP_

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

#include "common.hpp"


namespace rhakt {
namespace ilys {
namespace texture {

    GLuint create(const std::string& filename) {
        int x = 0, y = 0, comp = 0;
        auto rawimage = stbi_load(filename.c_str(), &x, &y, &comp, STBI_rgb_alpha);
        if(rawimage == NULL) { return NULL; }
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawimage);
        stbi_image_free(rawimage);
        return tex;
    }

    GLuint createSampler(GLuint filter, GLuint wrap) {
        GLuint sampler;
        glGenSamplers(1, &sampler);
        glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, filter);
        glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, filter);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrap);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrap);
        return sampler;
    }
    

} // end of namespace texture
} // end of namespace ilys
} // end of namespace rhakt


#endif