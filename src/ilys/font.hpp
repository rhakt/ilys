#ifndef _RHAKT_ILYS_ILYS_FONT_HPP_
#define _RHAKT_ILYS_ILYS_FONT_HPP_

#define STB_TRUETYPE_IMPLEMENTATION
#include "../lib/stb/stb_truetype.h"

#include "common.hpp"


namespace rhakt {
namespace ilys {
namespace font {

    class Font {
    public:
        Font(const int fontsize = 32, const int fontindex = 32, const int fontnum = 96)
            : FONT_SIZE(static_cast<float>(fontsize))
            , fdata(std::unique_ptr<stbtt_bakedchar[]>(new stbtt_bakedchar[fontnum]))
            , fontindex(fontindex), fontnum(fontnum) {}
        GLuint create(const std::string& filename) {
            unsigned char temp_bitmap[512*512];
            std::string buf;
            util::loadfile(filename, true, buf);
            std::unique_ptr<unsigned char[]> ttf_buffer(new unsigned char[buf.size()]);
            std::copy(buf.begin(), buf.end(), ttf_buffer.get());
            stbtt_BakeFontBitmap(ttf_buffer.get(), 0, FONT_SIZE, temp_bitmap, 512, 512, fontindex, fontnum, fdata.get());
            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
            return tex;
        }

        void getPosUv(const char ch, std::array<float, 2>& fpos, std::array<float, 2>& uvoff, std::array<float, 2>& uvsz, std::array<float, 2>& pos, std::array<int, 2>& sz) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(fdata.get(), 512, 512, ch-32, &fpos[0], &fpos[1], &q, 1);
            uvoff[0] = q.s0;
            uvoff[1] = q.t0;
            uvsz[0] = q.s1 - q.s0;
            uvsz[1] = q.t1 - q.t0;
            pos[0] = (q.x0 + q.x1) * 0.5f;
            pos[1] = (q.y0 + q.y1) * 0.5f;
            sz[0] = static_cast<int>(q.x1 - q.x0);
            sz[1] = static_cast<int>(q.y1 - q.y0);
        }

    private:
        std::unique_ptr<stbtt_bakedchar[]> fdata;
        const float FONT_SIZE = 32.f;
        const int fontindex;
        const int fontnum;
    };


} // end of namespace font
} // end of namespace ilys
} // end of namespace rhakt


#endif