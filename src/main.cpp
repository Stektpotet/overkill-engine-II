#define GLM_ENABLE_EXPERIMENTAL
#define GFX_IMPLEMENTATION
#define GFX_NO_TERMINATION_ON_GL_ERROR

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define DEBUG_GFX

#include <gfx.h>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Camera.hpp"
#include "ResourceLoader.h"


void processError(int code, const char* description) 
{ GFX_ERROR("%s - %s", glewGetErrorString(code), description); }

void render();
void update(float deltaTime);
void lateUpdate(float deltaTime);

GLFWwindow* window;
ShaderProgram p;
Camera cam;
glm::vec2 windowSize;

void processKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE) { glfwSetWindowShouldClose(window, GLFW_TRUE); }
}
void processCursorPosition(GLFWwindow* window, double x, double y)
{
}
void processMouseButtons(GLFWwindow* window, int button, int action, int mods) 
{
}

glm::uint packSnorm10x3_2Rev(glm::vec3 const& v) {
	const auto DISCARD_MASK = 1023;
	const auto MAX = 511;

	float magnitude = glm::length(v);
	GLuint x =  GLuint(v.x * MAX) & DISCARD_MASK;
	GLuint y =  GLuint(v.y * MAX) & DISCARD_MASK;
	GLuint z =  GLuint(v.z * MAX) & DISCARD_MASK;

	return 0 | (z << 20) | (y << 10) | (x << 0);
}
glm::uint packSnorm10x3_2Rev(glm::vec3 const& v, bool const& flag0, bool const& flag1) {
	const auto DISCARD_MASK = 1023;
	const auto MAX = 511;

	float magnitude = glm::length(v);
	GLuint x = GLuint(v.x * MAX) & DISCARD_MASK;
	GLuint y = GLuint(v.y * MAX) & DISCARD_MASK;
	GLuint z = GLuint(v.z * MAX) & DISCARD_MASK;

	return flag0 << 31 | flag1 << 30 | (z << 20) | (y << 10) | (x << 0);
}

glm::uint16 packTexCoords(glm::vec2 const& v) {
	const auto DISCARD_MASK = 511;
	const auto MAX = 255;

	float magnitude = glm::length(v);
	GLuint x = GLuint(v.x * MAX) & DISCARD_MASK;
	GLuint y = GLuint(v.y * MAX) & DISCARD_MASK;

	return (y << 8) | (x << 0);
}

struct vertex 
{
	glm::vec2 pos;
	glm::vec4 color;
};
static const vertex verts[] = {
	  //position     color
	{ {  0.9, -0.9}, {1,0,0,1} },
	{ {  0.9,  0.9}, {0,1,0,1} },
	{ { -0.9, -0.9}, {0,0,1,1} },
	{ { -0.9,  0.9}, {0,0,0,1} },
	{ {  0.5, -0.5}, {0,0,0,1} },
	{ {  0.5,  0.5}, {0,0,1,1} },
	{ { -0.5, -0.5}, {0,1,0,1} },
	{ { -0.5,  0.5}, {1,0,0,1} },
};

static glm::uint positions[] = {
	//positions
	packSnorm10x3_2Rev(glm::vec3{ -0.5f, -0.5f,  0.5f }),	// 0
	packSnorm10x3_2Rev(glm::vec3{  0.5f, -0.5f,  0.5f }),	// 1	F
	packSnorm10x3_2Rev(glm::vec3{  0.5f,  0.5f,  0.5f }),	// 2
	packSnorm10x3_2Rev(glm::vec3{ -0.5f,  0.5f,  0.5f }),	// 3
								// 
	packSnorm10x3_2Rev(glm::vec3{ -0.5f, -0.5f, -0.5f }),	// 4
	packSnorm10x3_2Rev(glm::vec3{ -0.5f, -0.5f,  0.5f }),	// 5	L
	packSnorm10x3_2Rev(glm::vec3{ -0.5f,  0.5f,  0.5f }),	// 6
	packSnorm10x3_2Rev(glm::vec3{ -0.5f,  0.5f, -0.5f }),	// 7
								// 
	packSnorm10x3_2Rev(glm::vec3{  0.5f, -0.5f,  0.5f }),	// 8
	packSnorm10x3_2Rev(glm::vec3{  0.5f, -0.5f, -0.5f }),	// 9	R
	packSnorm10x3_2Rev(glm::vec3{  0.5f,  0.5f, -0.5f }),	// 10
	packSnorm10x3_2Rev(glm::vec3{  0.5f,  0.5f,  0.5f }),	// 11
								// 
	packSnorm10x3_2Rev(glm::vec3{ -0.5f, -0.5f, -0.5f }),	// 12
	packSnorm10x3_2Rev(glm::vec3{  0.5f, -0.5f, -0.5f }),	// 13	U
	packSnorm10x3_2Rev(glm::vec3{  0.5f, -0.5f,  0.5f }),	// 14
	packSnorm10x3_2Rev(glm::vec3{ -0.5f, -0.5f,  0.5f }),	// 15
								// 
	packSnorm10x3_2Rev(glm::vec3{  0.5f, -0.5f, -0.5f }),	// 18
	packSnorm10x3_2Rev(glm::vec3{ -0.5f, -0.5f, -0.5f }),	// 19	B
	packSnorm10x3_2Rev(glm::vec3{ -0.5f,  0.5f, -0.5f }),	// 16
	packSnorm10x3_2Rev(glm::vec3{  0.5f,  0.5f, -0.5f }),	// 17
								// 
	packSnorm10x3_2Rev(glm::vec3{ -0.5f,  0.5f,  0.5f }),	// 20
	packSnorm10x3_2Rev(glm::vec3{  0.5f,  0.5f,  0.5f }),	// 21	O
	packSnorm10x3_2Rev(glm::vec3{  0.5f,  0.5f, -0.5f }),	// 22
	packSnorm10x3_2Rev(glm::vec3{ -0.5f,  0.5f, -0.5f })	// 23
};

static glm::uint16 uvs[] = {
	//uvs
	packTexCoords(glm::vec2(0, 0)),
	packTexCoords(glm::vec2(1, 0)),
	packTexCoords(glm::vec2(1, 1)),
	packTexCoords(glm::vec2(0, 1)),

	packTexCoords(glm::vec2(0, 0)),
	packTexCoords(glm::vec2(1, 0)),
	packTexCoords(glm::vec2(1, 1)),
	packTexCoords(glm::vec2(0, 1)),

	packTexCoords(glm::vec2(0, 0)),
	packTexCoords(glm::vec2(1, 0)),
	packTexCoords(glm::vec2(1, 1)),
	packTexCoords(glm::vec2(0, 1)),

	packTexCoords(glm::vec2(0, 0)),
	packTexCoords(glm::vec2(1, 0)),
	packTexCoords(glm::vec2(1, 1)),
	packTexCoords(glm::vec2(0, 1)),
	
	packTexCoords(glm::vec2(0, 0)),
	packTexCoords(glm::vec2(1, 0)),
	packTexCoords(glm::vec2(1, 1)),
	packTexCoords(glm::vec2(0, 1)),

	packTexCoords(glm::vec2(0, 0)),
	packTexCoords(glm::vec2(1, 0)),
	packTexCoords(glm::vec2(1, 1)),
	packTexCoords(glm::vec2(0, 1)),
};
static const GLuint elements[] = {
#define MakeQuad(x) x, x+1, x+2, x+2, x+3, x,
	MakeQuad(0)
	MakeQuad(4)
	MakeQuad(8)
	MakeQuad(12)
	MakeQuad(16)
	MakeQuad(20)
#undef MakeQuad
	//0, 1, 2,
	//2, 3, 0,
	//
	//4, 5, 6,
	//6, 7, 4,
	//
	//1, 6, 7,
	//7, 2, 1,
	//
	//8, 9, 1,
	//1, 0, 8,
	//
	//10, 11, 9,
	//9,  8,  10,
	//
	//12, 13, 11,
	//11, 10, 12
};
/*
VBO, VAO
  ^ render batching
Mesh

Blocks - Entities

*/

int main(void)
{
#pragma region Setup Context


	if (int i = glfwInit(); i == GLFW_FALSE) {
		GFX_ERROR("GLFW3: Failed initialization");
		return 100;
	}

	glewExperimental = true; // Needed for core profile
	glfwSetErrorCallback(processError);

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	//auto mName = glfwGetMonitorName(glfwGetPrimaryMonitor());
	auto monitor = glfwGetPrimaryMonitor();
	auto vidMode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	//
	GFX_INFO("dimensions: %dx%d", vidMode->width, vidMode->height);
	//GFX_INFO("Monitors: %d", monitorCount);
	windowSize = { vidMode->width*0.4f, vidMode->height*0.4f };
	window = glfwCreateWindow(windowSize.x, windowSize.y, "HelloWorld", nullptr, nullptr);
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
	cam = Camera(60, windowSize.x / windowSize.y);

	glfwSetKeyCallback(window, processKeys);
	glfwSetCursorPosCallback(window, processCursorPosition);
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


	VertexArray vao;

	IndexBuffer<GLuint> ibo(sizeof(elements), elements);
	
	VertexBuffer vbo(
		sizeof(positions) + sizeof(uvs),
		{ 
			{sizeof(positions),positions}, 
			{sizeof(uvs), uvs}
		}
	);

	//VertexBuffer vbo2 = VertexBuffer(sizeof(verts), verts);

	ContinuousVertexLayout layout;

	////unpacked:
	//// 3 * 4 = 12 | 12 * 24 = 288b
	//// 2 * 4 = 8  | 8 * 24  = 192b
	////						= 480 bytes
	layout.pushAttrib<GL_FLOAT, 3, 24>("position");
	layout.pushAttrib<GL_FLOAT, 2, 24>("uv");

	//packed:
	// 1 * 4 = 4 | 4 * 24 = 96b
	// 1 * 2 = 2 | 2 * 24 = 48b
	//					  = 144 bytes
/*
	layout.pushAttribPacked<GL_INT_2_10_10_10_REV, 4, 24>("position");
	layout.pushAttribPacked<GL_UNSIGNED_BYTE, 2, 24>("uv");		*/

	layout.applyToBuffer(vbo);

	p = createProgram("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
	

	Texture2D blockTextureAtlas;
	//int err = loadTextureAtlas("assets/textures/blocks.png", 16, &blockTextureAtlas);
	createNoiseTexture(glm::ivec2(512, 512), 3, &blockTextureAtlas);
	blockTextureAtlas.bind();
	
	GFX_GL_CALL(glUniform1i(p.getUniformLocation("blockAtlas"), 0));

	cam.transform.position = { -4, 0, 0 };
	cam.transform.lookAt({ 0,0,0 });
	cam.setFoV(30);

	GFX_GL_CALL(glEnable(GL_CULL_FACE));
	GFX_GL_CALL(glFrontFace(GL_CCW));
	GFX_GL_CALL(glCullFace(GL_BACK));
	GFX_GL_CALL(glEnable(GL_DEPTH_TEST));


#pragma endregion

#pragma region GameLoop
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
	GFX_GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	Transform blockTransform = {
		glm::vec3{0,0,0},
		glm::vec3{1,1,1},
		glm::quatLookAt(glm::normalize(glm::vec3{1,1,1}), glm::vec3{0,1,0})
	};
	
	glm::mat4 mvp = cam.viewProjectionMatrix() * blockTransform.modelMatrix();
	
	GLuint mvpLocation = glGetUniformLocation(p.ID(), "MVP");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
	
	GFX_GL_CALL(glDrawElementsInstancedBaseVertex(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr, 4096, 0));

	glfwSwapBuffers(window);
}

void update(float deltaTime)
{

}


void lateUpdate(float deltaTime)
{
	const float moveSpeed = 4.0; //units per second
	const float mouseSensitivity = 0.01f;
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (glfwGetKey(window, GLFW_KEY_A)) 
	{
		cam.transform.position -= cam.transform.right() * moveSpeed * deltaTime;
	} 
	else if (glfwGetKey(window, GLFW_KEY_D)) 
	{
		cam.transform.position += cam.transform.right() * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		cam.transform.position += cam.transform.forward() * moveSpeed * deltaTime;
	}
	else if (glfwGetKey(window, GLFW_KEY_S))
	{
		cam.transform.position -= cam.transform.forward() * moveSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_Q))
	{
		cam.transform.position += cam.transform.up() * moveSpeed * deltaTime;
	}
	else if (glfwGetKey(window, GLFW_KEY_E))
	{
		cam.transform.position -= cam.transform.up() * moveSpeed * deltaTime;
	}
	mouseX = (fmax(fmin(mouseX, windowSize.x), 0) / windowSize.x) - 0.5;
	mouseY = 0.5 - (fmax(fmin(mouseY, windowSize.y), 0) / windowSize.y);
	GFX_DEBUG("(%f,%f)", mouseX, mouseY);

	cam.transform.rotation = glm::rotate(cam.transform.rotation, (float)mouseX*mouseSensitivity, cam.transform.up());
	cam.transform.rotation = glm::rotate(cam.transform.rotation, (float)mouseY*mouseSensitivity, -cam.transform.right());
}