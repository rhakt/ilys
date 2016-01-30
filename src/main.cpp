#if _DEBUG && _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#define GLEW_NO_GLU
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>
#include <lz4.h>
#include <boost/network/protocol/http/client.hpp>
#include <boost/asio.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <iostream>

// おまじない
#if _MSC_VER
FILE _iob[] ={*stdin, *stdout, *stderr};
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
#endif

auto main()-> int {

#if _DEBUG && _MSC_VER
	// check memory leak (only VS)
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	
	
	// リクエスト作成
	boost::network::http::client::request request("http://www.boost.org/");
	request<< boost::network::header("Connection", "close");

	// GETで通信
	boost::network::http::client client;
	boost::network::http::client::response response = client.get(request);

	//レスポンスヘッダーを書き出し
	typedef boost::network::headers_range<boost::network::http::client::response>::type response_headers;
	boost::for_each(
		headers(response),
		[](const response_headers::value_type& value)->void
	{
		std::cout << value.first << ": " << value.second << std::endl;
	});

	//レスポンスボディの書き出し
	std::cout << "\n---Body---\n" << body(response) << std::endl;
	

	
	GLFWwindow* window;

    if (!glfwInit()) {
	    return -1;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
	bool isFullScreen = false;
    auto* pMonitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;
    
    window = glfwCreateWindow(800, 600, "Hello World", pMonitor, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        
		glfwSwapBuffers(window);
		glfwPollEvents();
    }

    glfwTerminate();
	
}