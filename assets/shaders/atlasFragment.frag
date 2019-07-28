#version 150

in vec2 texCoord;
out vec4 result;

uniform int atlasIndex;
uniform sampler2DArray blockAtlas;

void main() {
	result = texture(blockAtlas, vec3(texCoord, atlasIndex));
}