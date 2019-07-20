#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out vec2 texCoord;
uniform mat4 MVP = mat4(1);

void main() {

	texCoord = uv;
	vec3 offset = vec3(0, floor(3 * sin(gl_InstanceID*3.14*0.001)*0.25), gl_InstanceID);
	gl_Position = MVP * vec4(position + offset, 1);
}
