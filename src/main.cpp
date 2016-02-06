#include "main.hpp"

auto main()-> int {

#if _DEBUG && _MSC_VER
    // check memory leak (only VS)
    ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    using namespace rhakt;

    logger::setLevel(LOGLEVEL::DEBUG);

    // [stb_image.h] usage 
    // int x, y, comp;
    // auto buf = stbi_load("data/po.png", &x, &y, &comp, STBI_rgb_alpha);
    
    // [stb_truetype.h] usage
    // unsigned char ttf_buffer[1<<20];
    // unsigned char temp_bitmap[512*512];
    // stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
    //
    // fread(ttf_buffer, 1, 1<<20, fopen("c:/windows/fonts/times.ttf", "rb"));
    // stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits!
    //
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    /*    if(*text >= 32 && *text < 128) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(cdata, 512, 512, *text-32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
            glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0, q.y0);
            glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1, q.y0);
            glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1, q.y1);
            glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0, q.y1);
        }*/

    //rechor::Importer importer;
    //rechor::Scene scene;
    //importer.load("data/model/unitychan.rkr", scene);

    if(!glfwInit()) {
        logger::error("[glfw] initialize");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    bool isFullScreen = false;
    auto* pMonitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;
    
    auto window = glfwCreateWindow(800, 600, "ilys", pMonitor, NULL);
    if(!window) {
        glfwTerminate();
        logger::error("[glfw] create window");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        logger::error("[glew] initialize");
        return -1;
    }

    glClearColor(0.8f, 0.8f, 0.8f, 1.f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);


    while(!glfwWindowShouldClose(window)) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { break; } 
        //glfwGetWindowSize(window, &width, &height);
        //glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    
}
