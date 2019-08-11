#include "components/ParticleSystem.hpp"

namespace OK
{
ParticleSystem::ParticleSystem( int maxParticles,
                                ParticleSystemConfiguration config
                            ) : FlatGraphics(),
        m_maxParticles{maxParticles},
        m_count{0},
        m_oldestParticle{0},
        m_cooldown(0)
{
    pos =       new glm::vec3[maxParticles];
    rot =       new glm::vec3[maxParticles];
    scl =       new glm::vec3[maxParticles];
    vel =       new glm::vec3[maxParticles];
    angVel =    new glm::vec3[maxParticles];
    color =     new glm::vec4[maxParticles];
    life =      new float[maxParticles];
}

ParticleSystem::~ParticleSystem()
{
    delete pos;
    delete rot;
    delete scl;
    delete vel;
    delete angVel;
    delete color;
    delete life;
}

// Resets and relaunches the particle as a new one.
void ParticleSystem::launchParticle(int i)
{
    switch (m_cfg.volume)
    {
    case insideCirle:
        pos[i] =    glm::vec3(0,0,0);//m_gameObject->m_transform.getWorldPos();
        rot[i] =    glm::vec3(0, 0, OK::Util::random(0, glm::radians(360.0f)));
        scl[i] =    glm::vec3(m_cfg.startSize);
                
        glm::vec3 dirrr = glm::normalize(glm::vec3(OK::Util::random(-1,1), OK::Util::random(-1,1), 0));
        vel[i] = dirrr * m_cfg.startSpeed;
        
        
        angVel[i] = glm::vec3(0,0, OK::Util::random(0, m_cfg.startAngleSpeed));
        break;
    
    // default:
    //     GFX_ERROR("Invalid ParticleSystem configuration!");
    //     break;
    }

    color[i] = m_cfg.startColor;
    life[i] =   m_cfg.lifeTime;
}

void ParticleSystem::update(float deltaTime)
{
    m_cooldown -= deltaTime;
    if (m_cooldown <= 0)        // TODO: only allows 1 particle per frame.
    {
        m_cooldown =  1 / m_cfg.emissionsPerSec;

        for(float dt = deltaTime; dt >= m_cooldown; dt -= m_cooldown)
        {
            launchParticle(m_oldestParticle);
            m_oldestParticle = (m_oldestParticle + 1) % m_maxParticles;
            if (m_count < m_maxParticles) m_count++;
        }  
    }

    for (int i = 0; i < m_count; i++)
        life[i] -= (life[i] >= 0)? deltaTime : 0;

    for (int i = 0; i < m_count; i++)
    {
        vel[i] *= 1- m_cfg.drag * deltaTime;
        vel[i].y -= m_cfg.gravity * deltaTime;
    }

    for (int i = 0; i < m_count; i++)
        pos[i] += vel[i];

    for (int i = 0; i < m_count; i++)
        angVel[i] *= 1- m_cfg.angleDrag * deltaTime;
    
    for (int i = 0; i < m_count; i++)
        rot[i] += angVel[i];

    for (int i = 0; i < m_count; i++)
        scl[i] = glm::vec3(m_cfg.startSize) * 
                 OK::Util::lerp(m_cfg.startSize, m_cfg.endSize, life[i] / m_cfg.lifeTime);
    
    for (int i = 0; i < m_count; i++)
        color[i] = OK::Util::lerpColor(m_cfg.startColor, m_cfg.endColor, life[i] / m_cfg.lifeTime);
}


} // Namespace OK.