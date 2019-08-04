#version 450
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec3 texCoord;

uniform int text[64]; //supports 256 chars
uniform float spacing=0.5f;
uniform mat4 model = mat4(1);
uniform mat4 projection = mat4(1);

int character(in int index)
{
	int textIndex = index/4; //floor to int adress
	int byteShift = index - (textIndex*4);
	return (text[textIndex] >> (8 * byteShift)) & 0xff;

//	return (text[index / 4] >> (8 * (index - (index/4) * 4))) & 0xff;
}

void main()
{
	mat4 mp = projection * model;
    texCoord = vec3(uv, character(gl_InstanceID));
    gl_Position = projection * model * vec4(vec2(spacing*gl_InstanceID, 0) + position, 0.0, 1.0);
}