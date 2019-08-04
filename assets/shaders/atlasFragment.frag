#version 150

in vec3 texCoord;
out vec4 result;

uniform sampler2DArray image;
uniform vec4 color = vec4(1,1,1,1);

void main() {
	result = color * texture(image, texCoord);
}