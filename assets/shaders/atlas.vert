#version 450
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec3 texCoord;

uniform int atlasIndex = 3;
uniform mat4 model = mat4(1);
uniform mat4 projection = mat4(1);

void main()
{
    texCoord = vec3(uv, atlasIndex);
    gl_Position = projection * model * vec4(position, 0.0, 1.0);
}