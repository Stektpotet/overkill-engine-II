#version 330 core
in vec2 texCoord;
out vec4 result;

uniform sampler2D image;
uniform vec4 spriteColor = vec4(1,1,1,1);

void main()
{    
    result = spriteColor * texture(image, texCoord);
}  