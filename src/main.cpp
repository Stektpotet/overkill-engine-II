
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
#include "components/Sprite.hpp"
#include "components/HelloWorld.hpp"
#include "components/TextInstanced.hpp"
#include "components/Rigidbody.hpp"
#include "components/ParticleSystemSprite.hpp"
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
std::srand(time(NULL));	

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
	glClearColor(0, 0, 0, 1.0f);
	
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
   
	// auto gameObjectPac = OK::Scene::currentScene->makeGameObject("PacmanObject");
	// gameObjectPac->m_transform.position = glm::vec3((windowSize.x/2) -16, windowSize.y-32, 0);
    // {
	// 	OK::TextureAtlas texture;
    //     loadTextureAtlas("assets/textures/pacman.png", 2, &texture);
    //    	auto sp = gameObjectPac->addComponent<OK::AnimatedSprite>(texture, 0.3f, -1, true, true);
    //     sp->m_size = { 64,64 };
    //     sp->m_offset = sp->m_size * -0.5f;
    // }
	// auto pacmanRb = gameObjectPac->addComponent<OK::Rigidbody>(true);
	// pacmanRb->m_angularVelocity = glm::vec3(0, 0, 1);

 	// auto gameObjectHello = OK::Scene::currentScene->makeGameObject("HelloWorldObject");  
    // { //TODO: implement animatedSpriteRenderer into the graphicscomponent pipeline
    //     OK::TextureAtlas texture;
    //     loadTextureAtlas("assets/textures/loading.png", 4, &texture);
    //     auto sp = gameObjectHello->addComponent<OK::AnimatedSprite>(texture, 1, 15);
	// 	sp->m_size = { 150,150 };
    //     sp->m_offset = sp->m_size * -0.5f;
    // }

	// auto gameObjectText = OK::Scene::currentScene->makeGameObject("TextObject");
	// gameObjectText->m_transform.position = glm::vec3(0, 0, 0);
    // {
    //     auto txt = gameObjectText->addComponent<OK::TextInstanced>("I am sowtfare delevoper. yiep yiepyiep!");
    //     txt->m_size = { 34, 34 };
    //     txt->m_pivot = { 340, 0 };
    //     txt->m_offset = { -346, -80 };
    // }
	// //gameObjectText->m_transform.m_parent = &gameObjectPac->m_transform;
	
 	auto gameObjectParticleSystem = OK::Scene::currentScene->makeGameObject("ParticleSystemObject");  
    { //TODO: implement animatedSpriteRenderer into the graphicscomponent pipeline
		
		gameObjectParticleSystem->m_transform.position = glm::vec3(windowSize.x/2, windowSize.y/2, 0);
        
		OK::Texture2D texture;
        loadTexture("assets/textures/squareParticle.png", &texture);
		OK::ParticleSystemConfiguration config;
		config.volume = OK::EmissionVolume::onCircleEdge;
		config.worldSpace = true;
		config.emissionsPerSec = 3100;
		config.emissionRadius = 150;
		config.gravity = 5;
		config.startSpeed = 64;
		config.startScale = 4.3f;
		config.endScale = 1.3f;
		config.drag = 0.3f;
		config.startColor =  glm::vec4(1, 0, 0, 1);	
		config.endColor =    glm::vec4(0, 0.2f, 1, 0.4f);
        auto ps = gameObjectParticleSystem->addComponent<OK::ParticleSystemSprite>(texture, 10000, config);

		auto sp = gameObjectParticleSystem->addComponent<OK::Sprite>(texture);
		sp->m_color = {0, 1, 0, 1};
		sp->m_size = {20, 20};
		sp->m_offset = glm::vec2(sp->m_size.x* -0.5f, sp->m_size.y* -0.5f);
		sp->m_pivot = {0.5f, 0.5f};

		auto rb = gameObjectParticleSystem->addComponent<OK::Rigidbody>();
		rb->m_angularVelocity = {0, 0, 0.8f};
	}

	auto gameObjectFrameCounter = OK::Scene::currentScene->makeGameObject("FrameCounterObject");
	gameObjectFrameCounter->m_transform.position = glm::vec3(windowSize.x-60,0, 0);
        auto txtFrameCounter = gameObjectFrameCounter->addComponent<OK::TextInstanced>("00");
        txtFrameCounter->m_size = { 34, 34 };
		txtFrameCounter->m_color = {0.1f, 1, 0.1f, 1};

    OK::Scene::currentScene->prepareGraphics();
	
	float totalTime = 0;
	double lastTime = glfwGetTime();
	char frameCounterString[10];

	while (!glfwWindowShouldClose(window)) {
		
		// Time management: 
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		glfwPollEvents();		// process input
		totalTime += deltaTime;

		// if (deltaTime < (float)1/c_frameLimit)		// TODO: make smarter, so if the last frame took long, don't wait the full frame time.
		// 	continue;

		lastTime = currentTime;
		sprintf(frameCounterString, "%d", (int)(1/deltaTime));
		txtFrameCounter->setText(frameCounterString);
	
		// Debug GameObject transformations:
		// {
		// 	glm::vec3 pos = glm::vec3(
		// 			windowSize.x/2 + 100 * glm::sin(totalTime * 0.05f * deltaTime),
		// 			windowSize.y/2 + 100 * glm::cos(totalTime * 0.05f * deltaTime),
		// 			0);
		// 	gameObjectHello->m_transform.position = pos;
		// }
		// {
		// 	glm::vec3 scl = glm::vec3(
		// 		glm::abs(glm::sin(totalTime * 0.01f * deltaTime) * 0.8f) + 0.2f,
		// 		1,
		// 		1
		// 	);
		// 	gameObjectPac->m_transform.scale = scl;
		// }
		// // Pacman elastic bounce on ground.
		// if (pacmanRb->gameObject().m_transform.position.y < 0 && pacmanRb->m_velocity.y < 0)
		// 	pacmanRb->addForce(glm::vec3(0, -pacmanRb->m_velocity.y,0), OK::ForceMode::velocityChange);

		update(deltaTime);		// update

        render();				// batch -> render to g-buffer -> render to framebuffer

		lateUpdate(deltaTime);	// lateupdate

		  						// pass framebuffer through post processing

	}
#pragma endregion
	glfwTerminate();
	//cleanup
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
