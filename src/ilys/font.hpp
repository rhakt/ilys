#ifndef _RHAKT_ILYS_ILYS_FONT_HPP_
#define _RHAKT_ILYS_ILYS_FONT_HPP_

#define STB_TRUETYPE_IMPLEMENTATION
#include "../lib/stb/stb_truetype.h"

#include "common.hpp"


namespace rhakt {
namespace ilys {
namespace font {

    GLuint create(const std::string& filename) {
        stbtt_bakedchar fdata[96]; // ASCII 32..126 is 95 glyphs
        unsigned char temp_bitmap[512*512];
        std::string buf;
        util::loadfile(filename, true, buf);
        std::unique_ptr<unsigned char[]> ttf_buffer(new unsigned char[buf.size()]);
        std::copy(buf.begin(), buf.end(), ttf_buffer.get());
        stbtt_BakeFontBitmap(ttf_buffer.get(), 0, 64.0, temp_bitmap, 512, 512, 32, 64, fdata); // no guarantee this fits
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);


        return tex;
    }
    

} // end of namespace font
} // end of namespace ilys
} // end of namespace rhakt


#endif