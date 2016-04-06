#ifndef _RHAKT_ILYS_ILYS_FONT_HPP_
#define _RHAKT_ILYS_ILYS_FONT_HPP_

#define STB_TRUETYPE_IMPLEMENTATION
#include "../lib/stb/stb_truetype.h"

#include "common.hpp"

#include <SDL.h>
#include <SDL_ttf.h>

#include "texture.hpp"


namespace rhakt {
namespace ilys {
namespace font {

    class Font {
    public:
        Font(const std::string& filename, const int fontsize = 32): FONT_SIZE(fontsize) {
            font = TTF_OpenFont(filename.c_str(), FONT_SIZE);
        }
        auto create(const std::string& str) {
            auto sf = TTF_RenderUTF8_Blended_Wrapped(font, str.c_str(), SDL_Color{255, 255, 255, 255}, 2000);
            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sf->w, sf->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sf->pixels);
            auto samp = texture::createSampler(GL_LINEAR, GL_CLAMP_TO_EDGE);
            return std::make_shared<texture::Texture>(tex, samp, ivec2{sf->w, sf->h});
        }
    private:
        const int FONT_SIZE;
        TTF_Font* font;
    };


} // end of namespace font
} // end of namespace ilys
} // end of namespace rhakt


#endif