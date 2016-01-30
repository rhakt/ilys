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
#include <portaudio.h>
//#include <boost/network/protocol/http/client.hpp>
//#include <boost/asio.hpp>
//#include <boost/range/algorithm/for_each.hpp>

#include <iostream>

#if _MSC_VER
FILE _iob[] ={*stdin, *stdout, *stderr};
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
#endif

#define NUM_SECONDS   (4)
#define SAMPLE_RATE   (44100)

typedef struct
{
	float left_phase;
	float right_phase;
}
paTestData;

static int patestCallback(const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData)
{
	/* Cast data passed through stream to our structure. */
	paTestData *data = (paTestData*)userData;
	float *out = (float*)outputBuffer;
	unsigned int i;
	(void)inputBuffer; /* Prevent unused variable warning. */

	for(i=0; i<framesPerBuffer; i++)
	{
		*out++ = data->left_phase;  /* left */
		*out++ = data->right_phase;  /* right */
									 /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
		data->left_phase += 0.01f;
		/* When signal reaches top, drop back down. */
		if(data->left_phase >= 1.0f) data->left_phase -= 2.0f;
		/* higher pitch so we can distinguish left and right. */
		data->right_phase += 0.03f;
		if(data->right_phase >= 1.0f) data->right_phase -= 2.0f;
	}
	return 0;
}
static paTestData data;


auto main()-> int {

#if _DEBUG && _MSC_VER
	// check memory leak (only VS)
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	PaStream *stream;
	PaError err;

	printf("PortAudio Test: output sawtooth wave.\n");
	/* Initialize our data for use by callback. */
	data.left_phase = data.right_phase = 0.0;
	/* Initialize library before making any other calls. */
	err = Pa_Initialize();
	if(err != paNoError) goto error;

	/* Open an audio I/O stream. */
	err = Pa_OpenDefaultStream(&stream,
		0,          /* no input channels */
		2,          /* stereo output */
		paFloat32,  /* 32 bit floating point output */
		SAMPLE_RATE,
		256,        /* frames per buffer */
		patestCallback,
		&data);
	if(err != paNoError) goto error;

	err = Pa_StartStream(stream);
	if(err != paNoError) goto error;

	/* Sleep for several seconds. */
	Pa_Sleep(NUM_SECONDS*1000);

	err = Pa_StopStream(stream);
	if(err != paNoError) goto error;
	err = Pa_CloseStream(stream);
	if(err != paNoError) goto error;
	Pa_Terminate();
	printf("Test finished.\n");
	return err;
error:
	Pa_Terminate();
	fprintf(stderr, "An error occured while using the portaudio stream\n");
	fprintf(stderr, "Error number: %d\n", err);
	fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
	return err;

	
	/*
	boost::network::http::client::request request("http://www.boost.org/");
	request<< boost::network::header("Connection", "close");

	boost::network::http::client client;
	boost::network::http::client::response response = client.get(request);

	typedef boost::network::headers_range<boost::network::http::client::response>::type response_headers;
	boost::for_each(
		headers(response),
		[](const response_headers::value_type& value)->void
	{
		std::cout << value.first << ": " << value.second << std::endl;
	});

	std::cout << "\n---Body---\n" << body(response) << std::endl;
	*/
    
	
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