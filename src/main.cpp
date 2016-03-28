#include "main.hpp"


auto main()-> int {

#if _DEBUG && _MSC_VER
    // check memory leak (only VS)
    ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    using namespace rhakt;

    if(!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    bool isFullScreen = false;
    auto* pMonitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;

    const int windowWidth = 800;
    const int windowHeight = 600;

    auto window = glfwCreateWindow(windowWidth, windowHeight, "ilys", pMonitor, NULL);
    if(!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        return -1;
    }
    
    
    // [stb_image.h] usage 
    int x = 0, y = 0, comp = 0;
    auto rawimage = stbi_load("./data/texture/tex.png", &x, &y, &comp, STBI_rgb_alpha);
    
    // [stb_truetype.h] usage
    stbtt_bakedchar fdata[96]; // ASCII 32..126 is 95 glyphs
    unsigned char temp_bitmap[512*512];
    std::string buf;
    util::loadfile("./data/font/Avara.ttf", true, buf);
    std::unique_ptr<unsigned char[]> ttf_buffer(new unsigned char[buf.size()]);
    std::copy(buf.begin(), buf.end(), ttf_buffer.get());
    stbtt_BakeFontBitmap(ttf_buffer.get(), 0, 32.0, temp_bitmap, 512, 512, 32, 96, fdata); // no guarantee this fits
    
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

#define ILYS_FONT
#ifdef ILYS_FONT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);
#else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawimage);
#endif

    stbi_image_free(rawimage);
    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /*{
        stbtt_fontinfo font;
        int w, h, i, j, c = 'P', s = 20;
        stbtt_InitFont(&font, ttf_buffer.get(), stbtt_GetFontOffsetForIndex(ttf_buffer.get(), 0));
        auto bitmap = stbtt_GetCodepointBitmap(&font, 0, stbtt_ScaleForPixelHeight(&font, s), c, &w, &h, 0, 0);

        for(j=0; j < h; ++j) {
            for(i=0; i < w; ++i)
                putchar(" .:ioVM@"[bitmap[j*w+i]>>5]);
            putchar('\n');
        }
    }*/
    
    auto in = ilys::Input::getInstance(window);
    //in.startInputString();
    
    // 2D setting
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    
    GLuint vao;
    GLuint program;
    {
        program = glCreateProgram();
        
        auto compile = [&](const std::string filename, GLuint type) {
            auto shader = glCreateShader(type);
            std::string buf;
            util::loadfile(filename, false, buf);
            const GLchar* source[] = {buf.c_str()};
            glShaderSource(shader, 1, source, NULL);
            glCompileShader(shader);
            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if(status == GL_FALSE) {
                GLint len;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
                std::unique_ptr<GLchar[]> log(new GLchar[len]);
                glGetShaderInfoLog(shader, len, NULL, log.get());
                std::cerr << fmt::format("failed to compile {}: {}", filename, (char*)log.get()) << std::endl;
                std::system("pause");
                std::exit(1);
            }
            return shader;
        };

        auto vertexShader = compile("./data/shader/vert.shader", GL_VERTEX_SHADER);
        auto fragmentShader = compile("./data/shader/frag.shader", GL_FRAGMENT_SHADER);

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        float vertices[] = {
            -0.5,  0.5,
            -0.5, -0.5,
             0.5, -0.5,
            -0.5,  0.5,
             0.5, -0.5,
             0.5,  0.5
        };
        float uvs[] = {
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

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        auto vertAttrib = glGetAttribLocation(program, "vPos");
        glEnableVertexAttribArray(vertAttrib);
        glVertexAttribPointer(vertAttrib, 2, GL_FLOAT, false, 2*4, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
        auto uvAttrib = glGetAttribLocation(program, "vUv");
        glEnableVertexAttribArray(uvAttrib);
        glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, false, 2*4, 0);

    }
    glUseProgram(program);
    
    auto wsUniform = glGetUniformLocation(program, "windowSize");
    const int windowSize[] ={windowWidth, windowHeight};
    glUniform2iv(wsUniform, 1, &windowSize[0]);

    auto szUniform = glGetUniformLocation(program, "size");
    const int size[] = {64, 64};
    glUniform2iv(szUniform, 1, &size[0]);

    auto texUniform = glGetUniformLocation(program, "tex");
    glUniform1i(texUniform, 0);

#ifdef ILYS_FONT
    float fpos[] ={400.f, 300.f};
    stbtt_aligned_quad q;
    stbtt_GetBakedQuad(fdata, 512, 512, 'A'-32, &fpos[0], &fpos[1], &q, 1);
    auto uvoffUniform = glGetUniformLocation(program, "uvOffset");
    const float uvoff[] ={q.s0, q.t0};
    glUniform2fv(uvoffUniform, 1, &uvoff[0]);

    auto uvszUniform = glGetUniformLocation(program, "uvSize");
    const float uvsz[] ={q.s1 - q.s0, q.t1 - q.t0};
    glUniform2fv(uvszUniform, 1, &uvsz[0]);

    std::cout << uvoff[0] << ", " << uvoff[1] << std::endl;
    std::cout << uvsz[0] << ", " << uvsz[1] << std::endl;

    auto posUniform = glGetUniformLocation(program, "pos");
    const float pos[] ={(q.x0 + q.x1) / 2, (q.y0 + q.y1) / 2};
    glUniform2fv(posUniform, 1, &pos[0]);
#else
    auto uvoffUniform = glGetUniformLocation(program, "uvOffset");
    const float uvoff[] ={0.f, 0.f};
    glUniform2fv(uvoffUniform, 1, &uvoff[0]);

    auto uvszUniform = glGetUniformLocation(program, "uvSize");
    const float uvsz[] ={1.f, 1.f};
    glUniform2fv(uvszUniform, 1, &uvsz[0]);

    auto posUniform = glGetUniformLocation(program, "pos");
    const float pos[] ={400.f, 300.f};
    glUniform2fv(posUniform, 1, &pos[0]);
#endif

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glClearColor(0.8f, 0.8f, 0.8f, 1.f);

    while(!glfwWindowShouldClose(window)) {
        if(in.getKey(GLFW_KEY_ESCAPE)) { break; } 
        //glfwGetWindowSize(window, &width, &height);
        //glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //if(in.getKey(GLFW_KEY_Z)) { std::cout << "press Z" << std::endl; }
        //if(in.getKey(GLFW_KEY_Z, false)) { std::cout << "trigger Z" << std::endl; }
        //auto str = in.getInputString();
        //if(!str.empty()) std::cout << "input:" << str << std::endl;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
