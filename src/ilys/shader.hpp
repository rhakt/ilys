#ifndef _RHAKT_ILYS_ILYS_SHADER_HPP_
#define _RHAKT_ILYS_ILYS_SHADER_HPP_

#include "common.hpp"

namespace rhakt {
namespace ilys {
namespace shader {

        GLuint compile(const std::string& buf, GLuint type) {
            auto shader = glCreateShader(type);
            const GLchar* source[] = { buf.c_str() };
            glShaderSource(shader, 1, source, NULL);
            glCompileShader(shader);
            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if(status == GL_FALSE) {
                GLint len;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
                std::unique_ptr<GLchar[]> log(new GLchar[len]);
                glGetShaderInfoLog(shader, len, NULL, log.get());
                std::cerr << fmt::format("failed to compile: {}", (char*)log.get()) << std::endl;
                return NULL;
            }
            return shader;
        }

        GLuint compileFile(const std::string& filename, GLuint type) {
            std::string buf;
            util::loadfile(filename, false, buf);
            return compile(buf, type);
        }

        GLuint program(GLuint vertexShader, GLuint fragmentShader) {
            GLuint program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);
            return program;
        }


        struct uniform_updater {
            static void update(GLuint uni, const std::array<float, 2>& val) {
                glUniform2fv(uni, 1, val.data());
            }
            static void update(GLuint uni, const std::array<int, 2>& val) {
                glUniform2iv(uni, 1, val.data());
            }
            static void update(GLuint uni, float val) {
                glUniform1f(uni, val);
            }
            static void update(GLuint uni, int val) {
                glUniform1i(uni, val);
            }
        };
        
        class sherd_base {
        public:
            virtual std::string to_str() = 0;
            virtual void bind(GLuint program) = 0;
        };
        typedef std::shared_ptr<sherd_base> sherd_type;
        
        class sherd : public sherd_base {
        public:
            explicit sherd(const std::string& str): str(str) {  }
            virtual std::string to_str() { return str; }
            virtual void bind(GLuint program) {}
        private:
            std::string str;
        };
        
        template <class T>
        class sherd_uniform final : public sherd {
        public:
            sherd_uniform(const std::string& type, const std::string& name)
                : sherd(fmt::format("uniform {} {};", type, name)), name(name) {}
            void update(const T& val_) {
                val = val_;
                uniform_updater::update(uni, val);
            }
            template <class F>
            void updater(const F&& f) {
                f(val);
                uniform_updater::update(uni, val);
            }
            virtual void bind(GLuint program) {
                uni = glGetUniformLocation(program, name.c_str());
            };
        private:
            GLuint uni;
            std::string name;
            T val;
        };
        template <class T>
        using sherd_uniform_type = std::shared_ptr<ilys::shader::sherd_uniform<T>>;
        

        class Shader {
        public:
            explicit Shader(const std::string& version) {
                add(fmt::format("#version {}", version));
            }
            template <class T, class... Args>
            explicit Shader(const std::string& version, T s, Args... args): Shader(version) {
                add(s);
                add(args...);
            }
            void add(const std::string& str) {
                sherds.push_back(std::make_shared<sherd>(str));
            }
            void add(sherd_type s) {
                sherds.push_back(s);
            }
            template <class T, class U, class... Args>
            void add(T t, U u, Args... args) {
                add(t);
                add(u, args...);
            }
            std::string to_str() {
                return std::accumulate(sherds.begin(), sherds.end(), std::string{}, [](const auto& str, const auto& s){
                    return str + s->to_str() + "\n";
                });
            }
            void bind(GLuint program) {
                for(auto s : sherds) { s->bind(program); }
            }
        private:
            std::vector<sherd_type> sherds;
        };
        

} // end of namespace shader
} // end of namespace ilys
} // end of namespace rhakt


#endif