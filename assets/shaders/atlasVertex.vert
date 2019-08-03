#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out vec2 texCoord;

//uniform mat4 MVP = mat4(1);
uniform mat4 model = mat4(1);
uniform mat4 projection = mat4(1);


void main() {

	texCoord = uv;
	gl_Position = /*MVP*/ projection * model * vec4(position, 1);
}
