#ifndef _RHAKT_ILYS_ILYS_RENDER_HPP_
#define _RHAKT_ILYS_ILYS_RENDER_HPP_


#include "common.hpp"


namespace rhakt {
namespace ilys {
namespace render {

    GLFWwindow* createWindow(const std::string& title, const int width, const int height) {
        
        if(!glfwInit()) { return nullptr; }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        auto window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if(!window) {
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        glewExperimental = true;
        if(glewInit() != GLEW_OK) {
            glfwTerminate();
            return nullptr;
        }
        return window;
    }

    template <class F>
    void update(GLFWwindow* window, const F& func) {
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);

        glClearColor(0.8f, 0.8f, 0.8f, 1.f);
        
        while(!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            if(!func()) { break; }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwTerminate();
    }
    

} // end of namespace render
} // end of namespace ilys
} // end of namespace rhakt


#endif