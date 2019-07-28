#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out vec2 texCoord;

uniform mat4 MVP = mat4(1);

void main() {

	texCoord = uv;
	gl_Position = MVP * vec4(position, 1);
}
