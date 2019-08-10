#pragma once
#include "components/GraphicsComponent.hpp"
#include "UtilityFunctions.hpp"

namespace OK
{

enum ParticleVolume
{
    insideCirle, onCircleEdge,  // 2D
    insideShere, onShereEdge    // 3D
};

struct ParticleSystemConfiguration
{   
    ParticleVolume volume = insideCirle;
    bool  worldSpace =      true;   // When false, the particles are transformed with the ParticleSystem's GameObject.
    float emissionsPerSec = 5;
    float emissionRadius =  0;
    float lifeTime =        5;      // Seconds a particle lives for.
    float startSpeed =      10;
    float startAngleSpeed = 10;
    float gravity =         5;      // Gravity on Y axis in worldspace.
    float drag =            0.05f;
    float angleDrag =       0.1f;
    float startSize =       50;
    float endSize =         10;
    glm::vec4 startColor =  glm::vec4(1, 1, 1, 1);
    glm::vec4 endColor =    glm::vec4(1, 1, 1, 0.5f);
};

// Containts and updates the data for all paricles.
// Subclasses of will be responsible for drawing them.
class ParticleSystem :public GraphicsComponent
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
    ParticleSystem( 
                    GameObject* gameObject, 
                    int ID,
                    int maxParticles,
                    ParticleSystemConfiguration config
                );
    ~ParticleSystem();
    
    ParticleSystemConfiguration m_cfg;
};
    
} // Namespace OK.