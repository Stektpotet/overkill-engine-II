#version 150

in vec2 texCoord;
out vec4 result;

uniform int atlasIndex = 3;
uniform sampler2DArray image;
uniform vec4 spriteColor = vec4(1,1,1,1);

void main() {
	result = spriteColor * texture(image, vec3(texCoord, atlasIndex));
}