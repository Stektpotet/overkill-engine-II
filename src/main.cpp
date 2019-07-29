
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define DEBUG_GFX
#include <gfx.h>

#include "UtilityFunctions.hpp"
#include "Structs.hpp"
#include "Input.hpp"
#include "ControllableCamera.hpp"
#include "GameObject.hpp"
#include "components/SpriteRenderer.hpp"
#include "components/HelloWorld.hpp"
#include "Scene.hpp"


void render();
void draw();
void update(float deltaTime);
void lateUpdate(float deltaTime);

GLFWwindow* window;
glm::vec2 windowSize;

OK::ControllableCamera cam;

void processKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE) { glfwSetWindowShouldClose(window, GLFW_TRUE); }
}
void processMouseButtons(GLFWwindow* window, int button, int action, int mods) 
{ 
}


int main(void)
{

#pragma region Setup Context


	if (int i = glfwInit(); i == GLFW_FALSE) {
		GFX_ERROR("GLFW3: Failed initialization");
		return 100;
	}

	glewExperimental = true; // Needed for core profile
	glfwSetErrorCallback(OK::Util::processError);

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); // remove the handlebar from the top of the window
	
	auto monitor = glfwGetPrimaryMonitor();
	auto vidMode = glfwGetVideoMode(monitor);
	
	GFX_INFO("dimensions: %dx%d", vidMode->width, vidMode->height);
	windowSize = { vidMode->width*0.4f, vidMode->height*0.4f };
	window = glfwCreateWindow(windowSize.x, windowSize.y, "HelloWorld", nullptr, nullptr);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#define TASKBAR 30
	glfwSetWindowPos(window, vidMode->width - windowSize.x, vidMode->height - windowSize.y - TASKBAR);
#undef TASKBAR
	if (window == nullptr)
	{
		GFX_ERROR("GLFW3: Failed window creation");
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	if (glewInit() != GLEW_OK) {
		GFX_ERROR("GLEW: Failed window creation");
		return -1;
	}
	cam = OK::ControllableCamera(60, windowSize.x / windowSize.y);

	glfwSetKeyCallback(window, processKeys);
	glfwSetCursorPosCallback(window, Input::OnCursorHover);
	glfwSetMouseButtonCallback(window, processMouseButtons);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	
	GFX_GL_CALL(glEnable(GL_MULTISAMPLE));

	GFX_INFO("Vendor: %s", glGetString(GL_VENDOR));
	GFX_INFO("Renderer: %s", glGetString(GL_RENDERER));
	GFX_INFO("Version: %s", glGetString(GL_VERSION));
	GFX_INFO("GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	GFX_INFO("Extensions: %s", glGetString(GL_EXTENSIONS));
#pragma endregion

#pragma region Static Setup

	cam.transform.position = { 0, 0, -0.5 };
	cam.transform.lookAt({ 0,0,0 });
	cam.setFoV(70);

	GFX_GL_CALL(glEnable(GL_CULL_FACE));
	GFX_GL_CALL(glFrontFace(GL_CCW));
	GFX_GL_CALL(glCullFace(GL_BACK));
	GFX_GL_CALL(glEnable(GL_DEPTH_TEST));

	 //Transparent sprites:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

#pragma endregion



#pragma region GameLoop
    
    OK::Scene::currentScene = new OK::Scene("HelloWorldScene", { });
    auto gameObject = OK::Scene::currentScene->makeGameObject("HelloWorldObject");
	Texture2D texture;
	loadTexture("assets/textures/sprite.png", &texture);
	auto sp = gameObject->addComponent<OK::SpriteRenderer>(texture);
    sp->m_size = { 150,150 };
    sp->m_offset = windowSize * (0.5f - 0.125f);
    sp->m_pivot = { 0.5f, 0.53f};

    //gameObject.addComponent(sp->getID());
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		glfwPollEvents();		// process input

		update(deltaTime);		// update
		
        render();				// batch -> render to g-buffer -> render to framebuffer

		lateUpdate(deltaTime);	// lateupdate

		  						// pass framebuffer through post processing

		lastTime = currentTime;
	}
#pragma endregion
	glfwTerminate();
	//cleanup
}

void render()
{
	draw();
	glfwSwapBuffers(window);
    GFX_GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void draw()
{
	// Draw Components:
	//OK::Component::Draw();
}

void update(float deltaTime)
{
    OK::Scene::Update(deltaTime);
}

void lateUpdate(float deltaTime)
{
	//cam.update(deltaTime);
}