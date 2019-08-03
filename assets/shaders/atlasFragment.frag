#version 150

in vec2 texCoord;
out vec4 result;

uniform int atlasIndex;
uniform sampler2DArray blockAtlas;
uniform vec4 color = vec4(1,1,1,1);

void main() {
	result = color * texture(blockAtlas, vec3(texCoord, atlasIndex));
}