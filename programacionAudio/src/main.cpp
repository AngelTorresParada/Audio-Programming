#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <glfw3.h>
#include <iostream>
#include "Vec2.h"
#include <vector>
#include <stdio.h>
#include "alc.h"
#include "al.h"

#include "Engine.h"
#include "Font.h"
#include "Sprite.h"
#include "World.h"
#include "AudioBuffer.h"
#include "AudioSource.h"
#include "AudioListener.h"
#include "AudioStream.h"



using namespace std;


template <typename T>
std::string stringFromNumber(T val) {
	std::ostringstream stream;
	stream << std::fixed << val;
	return stream.str();
}

ltex_t *loadTexture(const char *);


int main() {
	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);

	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, true);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}

	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);

	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	double mX = 0;
	double mY = 0;

	const Vec2 center(width / 2, height / 2);

	ALCdevice *device = alcOpenDevice(nullptr);
	ALCcontext *context = alcCreateContext(device, nullptr);

	alcMakeContextCurrent(context);

	/*
	AudioBuffer *buffer = AudioBuffer::load("./data/mutant.ogg");
	AudioSource *source = new AudioSource(buffer);
	*/

	AudioSource *source = AudioSource::load("./data/mutant.ogg");

	source->play();

	source->setLooping(true);

	float pitch = 1;


	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);
		glfwGetCursorPos(window, &mX, &mY);

		
		//OpenGL da excepción sin razón aparente...
		//lgfx_clearcolorbuffer(0.5f, 0.5f, 0.5f);

		AudioStream::updateAll();

	}
	
	alcDestroyContext(context);
	alcCloseDevice(device);

    return 0;
}





