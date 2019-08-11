#version 450
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec2 texCoord;

uniform vec3 pos[1000];
uniform mat4 model = mat4(1);
uniform mat4 projection = mat4(1);

uniform int size = 1000;

// layout(std140) uniform Particles comming soon!
// {
//     vec3 pos        [size];
//     vec3 scl        [size];
//     vec4 rot        [size];
//     vec4 color      [size];
// };


void main()
{
	mat4 mp = projection * model;
    texCoord = uv;

    gl_Position = projection * model * vec4(position.x + pos[gl_InstanceID].x * 0.01, 
                                            position.y + pos[gl_InstanceID].y *0.01, 
                                            pos[gl_InstanceID].z * 0, 
                                            1.0);

    // gl_Position = projection * model * vec4(pos[gl_InstanceID].x + position.x, 
    //                                         pos[gl_InstanceID].y + position.y, 
    //                                         pos[gl_InstanceID].z, 
    //                                         1.0);
}