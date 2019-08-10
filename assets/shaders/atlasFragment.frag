#version 430
uniform sampler2DArray image;uniform vec4 color=vec4(1,1,1,1);
in vec3 texCoord;
out vec4 result;
void main(){result=color*texture(image,texCoord);}