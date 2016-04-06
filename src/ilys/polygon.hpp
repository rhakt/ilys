#ifndef _RHAKT_ILYS_ILYS_POLYGON_HPP_
#define _RHAKT_ILYS_ILYS_POLYGON_HPP_


#include "common.hpp"


namespace rhakt {
namespace ilys {
namespace polygon {

    GLuint generate2DSquare() {
        GLuint vao;

        std::vector<float> buf = {
            -0.5,  0.5, 0.0, 0.0,
            -0.5, -0.5, 0.0, 1.0,
             0.5, -0.5, 1.0, 1.0,
            -0.5,  0.5, 0.0, 0.0,
             0.5, -0.5, 1.0, 1.0,
             0.5,  0.5, 1.0, 0.0
        };
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint vbo[1];
        glGenBuffers(sizeof(vbo)/sizeof(vbo[0]), &vbo[0]);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, buf.size() * sizeof(float), buf.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 4, 0);
        glEnableVertexAttribArray(1);
        int offset = sizeof(float) * 2;
        glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 4, (const void*)offset);

        return vao;
    }
    

} // end of namespace polygon
} // end of namespace ilys
} // end of namespace rhakt


#endif