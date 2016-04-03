#include "main.hpp"


auto main()-> int {

#ifndef NDEBUG
#if _MSC_VER
    // check memory leak (only VS)
    ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif

    using namespace rhakt::ilys;

    const int windowWidth = 800;
    const int windowHeight = 600;
    auto window = render::createWindow("ilys", windowWidth, windowHeight);
    
    //auto tex = ilys::texture::create("./data/texture/tex.png");
    font::Font f(32);
    auto tex = f.create("./data/font/Vegur-Regular.ttf");
    auto samp = texture::createSampler(GL_LINEAR, GL_CLAMP_TO_EDGE);

    auto in = Input::getInstance(window);
    in.startInputString();

    //auto vertexShader = ilys::shader::compileFile("./data/shader/vert.shader", GL_VERTEX_SHADER);
    //auto fragmentShader = ilys::shader::compileFile("./data/shader/frag.shader", GL_FRAGMENT_SHADER);
    
    auto uni_ws = std::make_shared<shader::sherd_uniform<std::array<int, 2>>>("ivec2", "windowSize");
    auto uni_sz = std::make_shared<shader::sherd_uniform<std::array<int, 2>>>("ivec2", "size");
    auto uni_tex = std::make_shared<shader::sherd_uniform<int>>("sampler2D", "tex");
    auto uni_uvoff = std::make_shared<shader::sherd_uniform<std::array<float, 2>>>("vec2", "uvOffset");
    auto uni_uvsz = std::make_shared<shader::sherd_uniform<std::array<float, 2>>>("vec2", "uvSize");
    auto uni_pos = std::make_shared<shader::sherd_uniform<std::array<float, 2>>>("vec2", "pos");
    
    shader::Shader vert2d("330", uni_pos, uni_sz, uni_ws, R"(
        in vec2 vPos;
        in vec2 vUv;
        out vec2 fUv;
        void main() {
            vec2 iws = 2.0 / windowSize;
            vec2 p = vec2(pos.x * iws.x - 1.0, -pos.y * iws.y + 1.0);
            fUv = vUv;
            gl_Position = vec4(p + vPos * size * iws, 0.0, 1.0);
        }
    )");
    shader::Shader frag2d("330", uni_tex, uni_uvoff, uni_uvsz, R"(
        in vec2 fUv;
        out vec4 outColor;
        void main() {
            vec4 tc = texture(tex, fUv * uvSize + uvOffset);
            outColor = vec4(tc.r, 0.0, 0.0, tc.r);
        }       
    )");

    auto vs = shader::compile(vert2d.to_str(), GL_VERTEX_SHADER);
    auto fs = shader::compile(frag2d.to_str(), GL_FRAGMENT_SHADER);
    auto program = shader::program(vs, fs);
    vert2d.bind(program);
    frag2d.bind(program);
    glUseProgram(program);
    uni_ws->update({windowWidth, windowHeight});
    uni_sz->update({32, 32});
    uni_tex->update(0);
    uni_uvoff->update({0.f, 0.f});
    uni_uvsz->update({1.f, 1.f});
    uni_pos->update({400.f, 300.f});

    auto vao = polygon::generate(program);

    std::string disp("");
    
    static auto updater = [&](){
        if(in.getKey(GLFW_KEY_ESCAPE)) { return false; }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glBindSampler(0, samp);
        
        if(in.getKey(GLFW_KEY_Z)) { std::cout << "press Z" << std::endl; }
        if(in.getKey(GLFW_KEY_Z, false)) { std::cout << "trigger Z" << std::endl; }
        auto str = in.getInputString();
        if(!str.empty()) { disp += str; std::cout << disp << std::endl; }
        if(!disp.empty() && in.getKey(GLFW_KEY_BACKSPACE, false)) {
            disp.erase(disp.length() - 1);
        }
        if(!disp.empty()) {
            std::array<float, 2> fpos = {0.f, 32.f};
            for(auto&& ch : disp) {
                std::array<float, 2> uvoff, uvsz, pos;
                std::array<int, 2> sz;
                f.getPosUv(ch, fpos, uvoff, uvsz, pos, sz);
                uni_uvoff->update(uvoff);
                uni_uvsz->update(uvsz);
                uni_pos->update(pos);
                uni_sz->update(sz);
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
        }
        
        in.refresh();

        return true;
    };

    render::update(window, updater);
    
}
