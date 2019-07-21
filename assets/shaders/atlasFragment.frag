#version 150

in vec3 texCoord;
out vec4 result;
uniform sampler2DArray blockAtlas;
//uniform sampler2D blockAtlas;

void main() {
	result = texture(blockAtlas, texCoord);
}