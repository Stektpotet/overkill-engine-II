#version 450
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec2 texCoord;
out vec4 partColor;

const int maxParticles = 10000;
uniform mat4 model = mat4(1);
uniform mat4 projection = mat4(1);

layout(std140, binding=0) buffer Particles
{
    mat4  model       [maxParticles];
    vec4  color       [maxParticles];
} particles;


void main()
{
    texCoord = uv;
    partColor = particles.color[gl_InstanceID];

    gl_Position = projection * model * particles.model[gl_InstanceID] * vec4(position,
                                            0, 
                                            1.0);
}