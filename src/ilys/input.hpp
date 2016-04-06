#ifndef _RHAKT_ILYS_ILYS_INPUT_HPP_
#define _RHAKT_ILYS_ILYS_INPUT_HPP_

#include "common.hpp"

namespace rhakt {
namespace ilys {
namespace input {
    
    class Input {
    private:
        static std::unordered_map<int, bool> pressed;
        static std::unordered_map<int, bool> pulsed;
        static std::vector<char> que;
        static bool inputStringFlag;

        static auto keycallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            if(action == GLFW_PRESS) {
                pulsed[key] = pressed[key] ? false : true;
                pressed[key] = true;
            } else if(action == GLFW_RELEASE) {
                pressed[key] = false;
                pulsed[key] = false;
            }
        }

        static auto charcallback(GLFWwindow* window, unsigned int codepoint) {
            if(inputStringFlag) { 
                que.push_back(static_cast<char>(codepoint));
            }
        }

        static auto& create(GLFWwindow* window) {
            static Input in;
            glfwSetKeyCallback(window, Input::keycallback);
            glfwSetCharCallback(window, Input::charcallback);
            return in;
        }

    public:
        static auto& getInstance(GLFWwindow* window) {
            static auto& in = create(window);
            return in;
        }
        
        static bool getKey(int key, bool cont = true) {
            return cont ? pressed[key] : pulsed[key];
        }
        
        static void startInputString() {
            inputStringFlag = true;
        }

        static void endInputString() {
            inputStringFlag = false;
        }

        static std::string getInputString() {
            std::string str(que.begin(), que.end());
            que.clear();
            return std::move(str);
        }

        static void refresh() {
            for(auto&& p : pulsed) { p.second = false; }
        }
    
    };

} // end of namespace input
} // end of namespace ilys
} // end of namespace rhakt


#endif