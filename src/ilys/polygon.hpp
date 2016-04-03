#ifndef _RHAKT_ILYS_ILYS_POLYGON_HPP_
#define _RHAKT_ILYS_ILYS_POLYGON_HPP_


#include "common.hpp"


namespace rhakt {
namespace ilys {
namespace polygon {

    GLuint generate(GLuint program) {
        GLuint vao;

        std::vector<float> vertices = {
            -0.5,  0.5,
            -0.5, -0.5,
            0.5, -0.5,
            -0.5,  0.5,
            0.5, -0.5,
            0.5,  0.5
        };
        std::vector<float> uvs = {
            0.0, 0.0,
            0.0, 1.0,
            1.0, 1.0,
            0.0, 0.0,
            1.0, 1.0,
            1.0, 0.0
        };

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vbo[2];
        glGenBuffers(2, &vbo[0]);

        auto vbo_gen = [&program](const std::string& name, GLuint vbo_, const std::vector<float>& buf){
            glBindBuffer(GL_ARRAY_BUFFER, vbo_);
            glBufferData(
                GL_ARRAY_BUFFER,
                buf.size() * sizeof(float),
                buf.data(),
                GL_STATIC_DRAW
                );
            auto attr = glGetAttribLocation(program, name.c_str());
            glEnableVertexAttribArray(attr);
            glVertexAttribPointer(attr, 2, GL_FLOAT, false, 2 * sizeof(float), 0);
            return attr;
        };

        vbo_gen("vPos", vbo[0], vertices);
        vbo_gen("vUv", vbo[1], uvs);

        return vao;
    }
    

} // end of namespace polygon
} // end of namespace ilys
} // end of namespace rhakt


#endif