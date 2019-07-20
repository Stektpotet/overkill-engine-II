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

#include "UtilityFunctions.hpp"
#include "Structs.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Input.hpp"
#include "ControllableCamera.hpp"
#include "GameObject.hpp"
#include "components/SpriteRenderer.hpp"
#include "components/HelloWorld.hpp"


void render();
void draw();
void update(float deltaTime);
void lateUpdate(float deltaTime);

GLFWwindow* window;
glm::vec2 windowSize;

// Cube rendering:
ShaderProgram shaderProgram;
VertexArray* vao;
VertexBuffer* vbo;
TextureAtlas blockTextureAtlas;

OK::ControllableCamera cam;
OK::GameObject gameObject;

void processKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE) { glfwSetWindowShouldClose(window, GLFW_TRUE); }
}
void processMouseButtons(GLFWwindow* window, int button, int action, int mods) 
{ 
}

static const OK::Struct::Vertex verts[] = {
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

#ifdef PACKED_VERTICES
#define VEC3_POS(glm_vec3) packSnorm10x3_2Rev(glm_vec3)
#define VEC2_UV(glm_vec2) packTexCoords(glm_vec2)
#else
#define VEC3_POS(glm_vec3) glm_vec3
#define VEC2_UV(glm_vec2) glm_vec2
#endif


#ifdef PACKED_VERTICES
static glm::uint positions[] = {
#else
static glm::vec3 positions[] = {
#endif
	//positions
	VEC3_POS((glm::vec3{ -0.5f, -0.5f,  0.5f })),	// 0
	VEC3_POS((glm::vec3{  0.5f, -0.5f,  0.5f })),	// 1	F
	VEC3_POS((glm::vec3{  0.5f,  0.5f,  0.5f })),	// 2
	VEC3_POS((glm::vec3{ -0.5f,  0.5f,  0.5f })),	// 3
								// 			   
	VEC3_POS((glm::vec3{ -0.5f, -0.5f, -0.5f })),	// 4
	VEC3_POS((glm::vec3{ -0.5f, -0.5f,  0.5f })),	// 5	L
	VEC3_POS((glm::vec3{ -0.5f,  0.5f,  0.5f })),	// 6
	VEC3_POS((glm::vec3{ -0.5f,  0.5f, -0.5f })),	// 7
								// 
	VEC3_POS((glm::vec3{  0.5f, -0.5f,  0.5f })),	// 8
	VEC3_POS((glm::vec3{  0.5f, -0.5f, -0.5f })),	// 9	R
	VEC3_POS((glm::vec3{  0.5f,  0.5f, -0.5f })),	// 10
	VEC3_POS((glm::vec3{  0.5f,  0.5f,  0.5f })),	// 11
								// 
	VEC3_POS((glm::vec3{ -0.5f, -0.5f, -0.5f })),	// 12
	VEC3_POS((glm::vec3{  0.5f, -0.5f, -0.5f })),	// 13	U
	VEC3_POS((glm::vec3{  0.5f, -0.5f,  0.5f })),	// 14
	VEC3_POS((glm::vec3{ -0.5f, -0.5f,  0.5f })),	// 15
								// 
	VEC3_POS((glm::vec3{  0.5f, -0.5f, -0.5f })),	// 18
	VEC3_POS((glm::vec3{ -0.5f, -0.5f, -0.5f })),	// 19	B
	VEC3_POS((glm::vec3{ -0.5f,  0.5f, -0.5f })),	// 16
	VEC3_POS((glm::vec3{  0.5f,  0.5f, -0.5f })),	// 17
								// 
	VEC3_POS((glm::vec3{ -0.5f,  0.5f,  0.5f })),	// 20
	VEC3_POS((glm::vec3{  0.5f,  0.5f,  0.5f })),	// 21	O
	VEC3_POS((glm::vec3{  0.5f,  0.5f, -0.5f })),	// 22
	VEC3_POS((glm::vec3{ -0.5f,  0.5f, -0.5f }))	// 23
};

#ifdef PACKED_VERTICES
static glm::uint16 uvs[] = {
#else
static glm::vec2 uvs[] = {
#endif
	//uvs
	VEC2_UV((glm::vec2(0, 0))),
	VEC2_UV((glm::vec2(1, 0))),
	VEC2_UV((glm::vec2(1, 1))),
	VEC2_UV((glm::vec2(0, 1))),

	VEC2_UV((glm::vec2(0, 0))),
	VEC2_UV((glm::vec2(1, 0))),
	VEC2_UV((glm::vec2(1, 1))),
	VEC2_UV((glm::vec2(0, 1))),

	VEC2_UV((glm::vec2(0, 0))),
	VEC2_UV((glm::vec2(1, 0))),
	VEC2_UV((glm::vec2(1, 1))),
	VEC2_UV((glm::vec2(0, 1))),

	VEC2_UV((glm::vec2(0, 0))),
	VEC2_UV((glm::vec2(1, 0))),
	VEC2_UV((glm::vec2(1, 1))),
	VEC2_UV((glm::vec2(0, 1))),
	
	VEC2_UV((glm::vec2(0, 0))),
	VEC2_UV((glm::vec2(1, 0))),
	VEC2_UV((glm::vec2(1, 1))),
	VEC2_UV((glm::vec2(0, 1))),

	VEC2_UV((glm::vec2(0, 0))),
	VEC2_UV((glm::vec2(1, 0))),
	VEC2_UV((glm::vec2(1, 1))),
	VEC2_UV((glm::vec2(0, 1))),
};
#ifdef PACKED_VERTICES
#undef PACKED_VERTICES
#endif
#undef VEC3_POS
#undef VEC2_UV

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
	glfwSetErrorCallback(OK::Util::processError);

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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

	vao = new VertexArray();

	IndexBuffer<GLuint> ibo(sizeof(elements), elements);
	
	vbo = new VertexBuffer(
		sizeof(positions) + sizeof(uvs),
		{ 
			{sizeof(positions),positions}, 
			{sizeof(uvs), uvs}
		}
	);

	//VertexBuffer vbo2 = VertexBuffer(sizeof(verts), verts);

	ContinuousVertexLayout layout;


#ifdef PACKED_VERTICES	
	//packed:
	// 1 * 4 = 4 | 4 * 24 = 96b
	// 1 * 2 = 2 | 2 * 24 = 48b
	//					  = 144 bytes
error: expected '(' for function-style cast or type construction
	layout.pushAttribPacked<GL_INT_2_10_10_10_REV, 4, 24>("position");
	layout.pushAttribPacked<GL_UNSIGNED_BYTE, 2, 24>("uv");
#else
	//unpacked:
	// 3 * 4 = 12 | 12 * 24 = 288b
	// 2 * 4 = 8  | 8 * 24  = 192b
	//						= 480 bytes
	layout.pushAttrib<GL_FLOAT, 3, 24>("position");
	layout.pushAttrib<GL_FLOAT, 2, 24>("uv");
#endif

	layout.applyToBuffer(*vbo);

	shaderProgram = createProgram("assets/shaders/atlasVertex.vert", "assets/shaders/atlasFragment.frag");
	

	int err = loadTextureAtlas("assets/textures/blocks.png", 16, &blockTextureAtlas);
	//createNoiseTexture(glm::ivec2(512, 512), 3, &blockTextureAtlas);
	blockTextureAtlas.bind();
	
	GFX_GL_CALL(glUniform1i(shaderProgram.getUniformLocation("blockAtlas"), 0));

	cam.transform.position = { -4, 0, 0 };
	cam.transform.lookAt({ 0,0,0 });
	cam.setFoV(70);

	GFX_GL_CALL(glEnable(GL_CULL_FACE));
	GFX_GL_CALL(glFrontFace(GL_CCW));
	GFX_GL_CALL(glCullFace(GL_BACK));
	GFX_GL_CALL(glEnable(GL_DEPTH_TEST));


#pragma endregion



#pragma region GameLoop

	gameObject = OK::GameObject("HelloWorldObject", glm::vec3(0,0,0), glm::vec3(1,1,1), glm::quat(0,0,0,1));
	gameObject.addComponent(OK::HelloWorld(&gameObject).getID());
	Texture2D texture;
	loadTexture("assets/textures/sprite.png", &texture);
	gameObject.addComponent(OK::SpriteRenderer(&gameObject, texture).getID());

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
	draw();
	glfwSwapBuffers(window);
}

void draw()
{
	// Draw Components:
	//OK::Component::Draw();

	// Draw stone cubes:
	vao->bind();
	blockTextureAtlas.bind();
	shaderProgram.bind();

	Transform blockTransform = {
		glm::vec3{0,0,0},
		glm::vec3{1,1,1},
		glm::quatLookAt(glm::normalize(glm::vec3{1,1,1}), glm::vec3{0,1,0})
	};
	
	glm::mat4 mvp = cam.viewProjectionMatrix() * blockTransform.modelMatrix();
	
	GLuint mvpLocation = glGetUniformLocation(shaderProgram.ID(), "MVP");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
	
	GFX_GL_CALL(glDrawElementsInstancedBaseVertex(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr, 4096, 0));
	vao->unbind();
	blockTextureAtlas.unbind();
	shaderProgram.unbind();
}

void update(float deltaTime)
{
	OK::Component::Update(deltaTime);
}

void lateUpdate(float deltaTime)
{
	cam.update(deltaTime);
}