#include "framework.h"

// csúcspont árnyaló
const char * vertSource = R"(
@VERT_SHADER@)";

// pixel árnyaló
const char * fragSource = R"(
@FRAG_SHADER@)";

const int winWidth = 600, winHeight = 600;

class GreenTriangleApp : public glApp {
	Geometry<vec2>* triangle = nullptr;  // geometria
	GPUProgram* gpuProgram = nullptr;	 // csúcspont és pixel árnyalók
public:
	GreenTriangleApp() : glApp("Green triangle") { }

	// Inicializáció, 
	void onInitialization() {
		triangle = new Geometry<vec2>;
		triangle->Vtx() = { vec2(-0.8f, -0.8f), vec2(-0.6f, 1.0f), vec2(0.8f, -0.2f) };
		triangle->updateGPU();
		gpuProgram = new GPUProgram(vertSource, fragSource);
	}

	// Ablak újrarajzolás
	void onDisplay() {
		glClearColor(0, 0, 0, 0);     // háttér szín
		glClear(GL_COLOR_BUFFER_BIT); // rasztertár törlés
		glViewport(0, 0, winWidth, winHeight);
		triangle->Draw(gpuProgram, GL_TRIANGLES, vec3(0.0f, 1.0f, 0.0f));
	}
};

GreenTriangleApp app;
