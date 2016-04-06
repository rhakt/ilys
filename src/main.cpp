#include "main.hpp"

// memo
class gil_lock {
public:
    gil_lock() { state_ = PyGILState_Ensure(); }
    ~gil_lock() { PyGILState_Release(state_); }
private:
    PyGILState_STATE state_;
};


int main(int argc, char **argv) {

#ifndef NDEBUG
#if _MSC_VER
    // check memory leak (only VS)
    ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif
    
    namespace bp = boost::python;
    
    Py_Initialize();
    
    auto global_ns = bp::import("__main__").attr("__dict__");
    bp::exec(R"(
from datetime import datetime
def hello(s):
    print("{} {}".format(s, "boost::python!"))
    return datetime.now().strftime("%Y/%m/%d %H:%M:%S")
    )", global_ns, global_ns);
   
    auto pyhello = global_ns["hello"];
    std::cout << bp::extract<char*>(pyhello("hello")) << std::endl;

    
    if(!Mix_Init(MIX_INIT_OGG)) {
        std::cerr << "Mix_Init: " << Mix_GetError() << std::endl;
        std::system("pause");
        return -1;
    }
    if(TTF_Init() == -1) {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
        return -1;
    }

    Mix_OpenAudio(44100, AUDIO_S16, 2, 4096);
    Mix_VolumeMusic(50);
    Mix_Music *music = Mix_LoadMUS("data/music/n23.ogg");
    if(!music) {
        std::cerr << "fail to load" << std::endl;
        std::system("pause");
        exit(1);
    }
    Mix_PlayMusic(music, 1);
    // http://sdl2referencejp.osdn.jp/SDL_mixer-functions-music.html

    using namespace rhakt::ilys;

    const int windowWidth = 800;
    const int windowHeight = 600;
    auto window = createWindow("ilys", windowWidth, windowHeight);
    
    auto samp = texture::createSampler(GL_LINEAR, GL_CLAMP_TO_EDGE);
    auto tex2 = std::make_shared<texture::Texture>("./data/texture/tex.png", samp);
    
    font::Font f("data/font/GenEiGothicM-Regular.ttf", 32);
    auto tex = f.create(u8"ユクモの破格のごときかー\nぴょえー！");
    
    auto in = input::Input::getInstance(window);
    in.startInputString();

    //auto vertexShader = ilys::shader::compileFile("./data/shader/vert.shader", GL_VERTEX_SHADER);
    //auto fragmentShader = ilys::shader::compileFile("./data/shader/frag.shader", GL_FRAGMENT_SHADER);
    
    auto uni_ws = shader::make_uniform<ivec2>("ivec2", "windowSize");
    auto uni_sz = shader::make_uniform<vec2>("vec2", "size");
    auto uni_tex = shader::make_uniform<int>("sampler2D", "tex");
    auto uni_uvoff = shader::make_uniform<vec2>("vec2", "uvOffset");
    auto uni_uvsz = shader::make_uniform<vec2>("vec2", "uvSize");
    auto uni_pos = shader::make_uniform<vec2>("vec2", "pos");
    auto uni_col = shader::make_uniform<vec4>("vec4", "col");
    
    shader::Shader vert2d("330", uni_pos, uni_sz, uni_ws, R"(
        layout (location = 0) in vec2 vPos;
        layout (location = 1) in vec2 vUv;
        out vec2 fUv;
        void main() {
            vec2 iws = 2.0 / windowSize;
            vec2 p = vec2(pos.x * iws.x - 1.0, -pos.y * iws.y + 1.0);
            fUv = vUv;
            gl_Position = vec4(p + vPos * size * iws, 0.0, 1.0);
        }
    )");
    shader::Shader frag2d("330", uni_tex, uni_uvoff, uni_uvsz, uni_col, R"(
        in vec2 fUv;
        out vec4 outColor;
        void main() {
            outColor = texture(tex, fUv * uvSize + uvOffset) * col;
        }       
    )");

    auto vs = shader::compile(vert2d.to_str(), GL_VERTEX_SHADER);
    auto fs = shader::compile(frag2d.to_str(), GL_FRAGMENT_SHADER);
    auto program = shader::program(vs, fs);
    vert2d.bind(program);
    frag2d.bind(program);
    glUseProgram(program);
    uni_ws->update({windowWidth, windowHeight});
    uni_sz->update({32.f, 32.f});
    uni_tex->update(0);
    uni_uvoff->update({0.f, 0.f});
    uni_uvsz->update({1.f, 1.f});
    uni_pos->update({400.f, 300.f});
    uni_col->update({1.f, 1.f, 1.f, 1.f});

    auto vao = polygon::generate2DSquare();

    std::string disp("");
    
    static auto updater = [&](){
        if(in.getKey(GLFW_KEY_ESCAPE)) { return false; }

        tex->use();

        if(in.getKey(GLFW_KEY_Z)) { std::cout << "press Z" << std::endl; }
        if(in.getKey(GLFW_KEY_Z, false)) { std::cout << "trigger Z" << std::endl; }
        auto str = in.getInputString();
        if(!str.empty()) { disp += str; std::cout << disp << std::endl; }
        if(!disp.empty() && in.getKey(GLFW_KEY_BACKSPACE, false)) {
            disp.erase(disp.length() - 1);
        }
        if(!disp.empty()) {
            uni_uvoff->update({0.0f, 0.0f});
            uni_uvsz->update({1.f, 1.f});
            uni_col->update({0.f, 1.f, 1.f, 1.f});
            auto sz = tex->getSize<vec2>();
            uni_pos->update({sz[0]/2, sz[1]/2});
            uni_sz->update(sz);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        tex2->use();
        uni_uvoff->update({0.0f, 0.0f});
        uni_uvsz->update({0.f, 0.f});
        uni_pos->update({400.f, 300.f});
        uni_sz->update({32.f, 32.f});
        uni_col->update({1.f, 1.f, 1.f, 1.f});
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        
        return true;
    };

    update(window, updater);

    Mix_FreeMusic(music);
    Mix_Quit();
    TTF_Quit();
    
    return 0;
}
