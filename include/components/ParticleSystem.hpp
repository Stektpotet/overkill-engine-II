#pragma once
#include "components/FlatGraphics.hpp"
#include "UtilityFunctions.hpp"


namespace OK
{

enum EmissionVolume
{
    insideCirle, onCircleEdge,  // 2D
    insideShere, onShereEdge    // 3D
};

struct ParticleSystemConfiguration
{   
    EmissionVolume volume = insideCirle;
    bool  worldSpace =      true;   // When false, the particles are transformed with the ParticleSystem's GameObject.
    float emissionsPerSec = 3100;
    float emissionRadius =  0;
    float lifeTime =        3;      // Seconds a particle lives for.
    float startSpeed =      280;
    float startAngleSpeed = 180;     // Degrees / second.
    float gravity =         190;      // Gravity on Y axis in worldspace.
    float drag =            0.6f;
    float angleDrag =       0.08f;
    float startScale =       5;
    float endScale =         0.1f;
    glm::vec4 startColor =  glm::vec4(1, 0, 0, 1);
    glm::vec4 endColor =    glm::vec4(0, 0, 1, 0.2f);
};

const int c_maxAllowedParticles = 10000;
struct ParticleData
{
    glm::vec3  pos    [c_maxAllowedParticles];
    glm::vec3  rot    [c_maxAllowedParticles];
    glm::vec3  scl    [c_maxAllowedParticles];
    glm::vec3  vel    [c_maxAllowedParticles];
    glm::vec3  angVel [c_maxAllowedParticles];
    glm::vec4  color  [c_maxAllowedParticles];
    float      life   [c_maxAllowedParticles];
};

struct ShaderData
{
    glm::mat4 model [c_maxAllowedParticles];
    glm::vec4 color [c_maxAllowedParticles];
};


// Containts and updates the data for all paricles.
// Subclasses of will be responsible for drawing them.
class ParticleSystem :public FlatGraphics
{
private:
    float m_cooldown;

    void launchParticle(int i);
protected:
    int   m_maxParticles;
    int   m_highestIndex;   // Counts how many indecies in the arrays are in use. Becomes maxParticles after a while.
    int   m_oldestParticle; // The index in the arrays which marks the "end", this counter is moved around as new paritlces are made.
    int   m_particlesCount;
    float m_playbackSpeed;
    GLuint m_SSBO = 0;
    ParticleData m_data;
    ShaderData m_shaderData;

    void update(float deltaTime) override;

public:
    ParticleSystem( int maxParticles,
                    ParticleSystemConfiguration config
                );
    
    bool m_emitting = true;
    ParticleSystemConfiguration m_cfg;

    int count();

};
    
} // Namespace OK.