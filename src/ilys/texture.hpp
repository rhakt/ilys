#ifndef _RHAKT_ILYS_ILYS_TEXTURE_HPP_
#define _RHAKT_ILYS_ILYS_TEXTURE_HPP_

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

#include "common.hpp"


namespace rhakt {
namespace ilys {
namespace texture {

    GLuint createSampler(GLuint filter, GLuint wrap) {
        GLuint sampler;
        glGenSamplers(1, &sampler);
        glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, filter);
        glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, filter);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrap);
        glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrap);
        return sampler;
    }

    class Texture {
    public:
        Texture(GLuint tex, GLuint samp, const ivec2& size): tex(tex), samp(samp), size(size) {}
        Texture(const std::string& filename, GLuint samp): samp(samp) {
            int comp = 0;
            auto rawimage = stbi_load(filename.c_str(), &size[0], &size[1], &comp, STBI_rgb_alpha);
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size[0], size[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, rawimage);
            stbi_image_free(rawimage);
        }
        void use(int num = 0) {
            glActiveTexture(GL_TEXTURE0 + num);
            glBindTexture(GL_TEXTURE_2D, tex);
            glBindSampler(num, samp);
        }
        template <class T = decltype(size)>
        T getSize() const { return T{static_cast<T::value_type>(size[0]), static_cast<T::value_type>(size[1])}; }
    private:
        GLuint tex;
        GLuint samp;
        ivec2 size;
    };
    

} // end of namespace texture
} // end of namespace ilys
} // end of namespace rhakt


#endif