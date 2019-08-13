#version 450 core
in vec2 texCoord;
in vec4 partColor;
out vec4 result;

uniform sampler2D image;
uniform vec4 color = vec4(1,1,1,1);

void main()
{    
    result = partColor * color * texture(image, texCoord);
}  