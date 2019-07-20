#version 150

in vec2 texCoord;
out vec4 result;
uniform sampler2D image;

void main() {
	result = texture(image, texCoord);
}