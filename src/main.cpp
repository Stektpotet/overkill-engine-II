
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define DEBUG_GFX

#include "UtilityFunctions.hpp"
#include "Structs.hpp"
#include "Input.hpp"
#include "ControllableCamera.hpp"
#include "components/AnimatedSprite.hpp"
#include "components/HelloWorld.hpp"
#include "components/Text.hpp"
#include "components/TextInstanced.hpp"
#include "components/Rigidbody.hpp"
#include "Scene.hpp"

const int c_frameLimit = 60;

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

	cam.transform.position = { 0, 0, -10.5 };
	cam.transform.lookAt({ 0,0,0 });
	cam.setFoV(80);

	GFX_GL_CALL(glEnable(GL_CULL_FACE));
	GFX_GL_CALL(glFrontFace(GL_CCW));
	GFX_GL_CALL(glCullFace(GL_BACK));
	//GFX_GL_CALL(glEnable(GL_DEPTH_TEST));

	 //Transparent sprites:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    //glDepthMask(GL_FALSE);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0); //Deprecated since OpenGL 4

#pragma endregion

#pragma region GameLoop
    OK::Scene::currentScene = new OK::Scene("HelloWorldScene", { });
    auto gameObjectHello = OK::Scene::currentScene->makeGameObject("HelloWorldObject");  
    { //TODO: implement animatedSpriteRenderer into the graphicscomponent pipeline
        OK::TextureAtlas texture;
        loadTextureAtlas("assets/textures/loading.png", 4, &texture);
        auto sp = gameObjectHello->addComponent<OK::AnimatedSprite>(texture, 1, 15);
		sp->m_size = { 150,150 };
        sp->m_offset = sp->m_size * -0.5f;
    }
	
	auto gameObjectPac = OK::Scene::currentScene->makeGameObject("PacmanObject");
	gameObjectPac->m_transform.position = glm::vec3(100, windowSize.y-32, 0);
    {
		OK::TextureAtlas texture;
        loadTextureAtlas("assets/textures/pacman.png", 2, &texture);
       	auto sp = gameObjectPac->addComponent<OK::AnimatedSprite>(texture, 0.3f, -1, true, true);
        sp->m_size = { 64,64 };
        sp->m_offset = sp->m_size * -0.5f;
    }
	auto pacmanRb = gameObjectPac->addComponent<OK::Rigidbody>(true);
	// pacmanRb->m_angularVelocity = glm::vec3(0, 0, 10);

	auto gameObjectText = OK::Scene::currentScene->makeGameObject("TextObject");
	gameObjectText->m_transform.position = glm::vec3(300, 300, 0);
    {
        auto txt = gameObjectText->addComponent<OK::TextInstanced>("I am sowtfare delevoper. yiep yiepyiep!");
        txt->m_size = { 34, 34 };
        txt->m_pivot = { 340, 0 };
        txt->m_offset = { -136, -136 };
    }
	{
		auto txt = gameObjectText->addComponent<OK::Text>("Hello World!!");
		txt->setSize(50);
	}
	
	auto gameObjectFrameCounter = OK::Scene::currentScene->makeGameObject("FrameCounterObject");
	gameObjectFrameCounter->m_transform.position = glm::vec3(windowSize.x-60,0, 0);
        auto txtFrameCounter = gameObjectFrameCounter->addComponent<OK::TextInstanced>("00");
        txtFrameCounter->m_size = { 34, 34 };
		txtFrameCounter->m_color = {0.1f, 1, 0.1f, 1};

    OK::Scene::currentScene->prepareGraphics();
	
	{	// Optional test:
		OK::Scene::currentScene->getGameObject("FrameCounterObject");			// Should succeed.
		std::shared_ptr<OK::GameObject> g = OK::Scene::currentScene->getGameObject("FrameCourdxcfgvnterObject");	// Should fail, print a warn.
		if (g == nullptr)
		{
			GFX_DEBUG("The thing i wanted wasn't there :(");
		}
		else
		{
			GFX_DEBUG("YAY, found the ting!");
		}
	}

	float totalTime = 0;
	double lastTime = glfwGetTime();
	char* frameCounterString = new char[10];

	while (!glfwWindowShouldClose(window)) {
		
		// Time management: 
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		glfwPollEvents();		// process input
		totalTime += deltaTime;

		if (deltaTime < (float)1/c_frameLimit)	// 60fps.
			continue;

		lastTime = currentTime;
		sprintf(frameCounterString, "%d", (int)(1/deltaTime));
		txtFrameCounter->setText(frameCounterString);
		

	
		// Debug GameObject transformations:
		{
			glm::vec3 pos = glm::vec3(
					windowSize.x/2 + 100 * glm::sin(totalTime),
					windowSize.y/2 + 100 * glm::cos(totalTime),
					0);
			glm::vec3 rot = glm::vec3(0, 0, glm::radians(90.0f) * glm::sin(totalTime));	
			glm::vec3 scl = glm::vec3(	(glm::abs(glm::cos(totalTime*3) * 0.7f)) + 0.3f,
										(glm::abs(glm::sin(totalTime*3) * 0.7f)) + 0.3f,
										 1);	

			gameObjectHello->m_transform.position = pos;
			gameObjectHello->m_transform.rotation = glm::quat(rot);
			gameObjectHello->m_transform.scale = scl;
		}
		{
			glm::vec3 pos = glm::vec3(
					windowSize.x/6 + 50 * glm::sin(totalTime * 2),
					windowSize.y/2 + 80 * glm::cos(totalTime * 2),
					0);
			glm::vec3 rot = glm::vec3(0, 0, glm::radians(30.0f) * glm::sin(totalTime));	
			gameObjectText->m_transform.position = pos;
			gameObjectText->m_transform.rotation = glm::quat(rot);
		}

		// Pacman elastic bounce on ground.
		if (pacmanRb->m_gameObject->m_transform.position.y < 0 && pacmanRb->m_velocity.y < 0)
			//pacmanRb->m_velocity.y = - pacmanRb->m_velocity.y;
			pacmanRb->addForce(glm::vec3(0, -pacmanRb->m_velocity.y,0), OK::ForceMode::velocityChange);
		// OK::Util::printTransform(pacmanRb->m_gameObject->m_transform);

		update(deltaTime);		// update

        render();				// batch -> render to g-buffer -> render to framebuffer

		lateUpdate(deltaTime);	// lateupdate

		  						// pass framebuffer through post processing

	}
#pragma endregion
	glfwTerminate();
	//cleanup
	delete frameCounterString;
    delete(OK::Scene::currentScene);
}

void render()
{
	draw();
	glfwSwapBuffers(window);
    GFX_GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void update(float deltaTime)
{
    OK::Scene::Update(deltaTime);
}

void lateUpdate(float deltaTime)
{
	//cam.update(deltaTime);
}

void draw()
{
	// Draw Components:	// TODO: have the scene handle this so not all scenes in memory draw all at once.
    OK::Scene::currentScene->draw();
}
