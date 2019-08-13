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
    // partColor = particles.color[gl_InstanceID];
    // partColor = vec4(life/5.0,1-(life/5.0), 1, 1);
    partColor = vec4(1, 1, 1, 1);
    
    // gl_Position =  projection * model * vec4(position,
    //                                         0, 
    //                                         1.0);
    
    
    gl_Position = projection * model * particles.model[gl_InstanceID] * vec4(position,
                                            0, 
                                            1.0);


    //gl_Position = particles.model[gl_InstanceID] * mp * vec4(1,1,1,1);
                                                            


    // SSBO:
    // gl_Position = mp * vec4(position.x + particles.pos[gl_InstanceID].x * 0.01, 
    //                                         position.y + particles.pos[gl_InstanceID].y * 0.01, 
    //                                         0, 
    //                                         1.0);
    
    //Vec3 pos array only:
    // gl_Position = projection * model * vec4(position.x + pos[gl_InstanceID].x * 0.01, 
    //                                         position.y + pos[gl_InstanceID].y *0.01, 
    //                                         pos[gl_InstanceID].z * 0, 
    //                                         1.0);

}