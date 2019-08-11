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
    float emissionsPerSec = 500;
    float emissionRadius =  0;
    float lifeTime =        5;      // Seconds a particle lives for.
    float startSpeed =      8;
    float startAngleSpeed = 10;
    float gravity =         2;      // Gravity on Y axis in worldspace.
    float drag =            0.002f;
    float angleDrag =       0;
    float startSize =       10;
    float endSize =         10;
    glm::vec4 startColor =  glm::vec4(1, 0, 0, 1);
    glm::vec4 endColor =    glm::vec4(0, 0, 1, 0.5f);
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
    int   m_count;
    int   m_oldestParticle;

    // Particle data:
    glm::vec3*  pos;
    glm::vec3*  rot;
    glm::vec3*  scl;
    glm::vec3*  vel;
    glm::vec3*  angVel;
    glm::vec4*  color;
    float*      life;

    void update(float deltaTime) override;

public:
    ParticleSystem( int maxParticles,
                    ParticleSystemConfiguration config
                );
    ~ParticleSystem();
    
    ParticleSystemConfiguration m_cfg;
};
    
} // Namespace OK.