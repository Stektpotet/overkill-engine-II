#include "components/ParticleSystem.hpp"

namespace OK
{
ParticleSystem::ParticleSystem( int maxParticles,
                                ParticleSystemConfiguration config
                            ) : FlatGraphics(),
        m_cfg{config},
        m_highestIndex{0},
        m_oldestParticle{0},
        m_particlesCount{0},
        m_cooldown{0},
        m_playbackSpeed{1}
{
    if (maxParticles > c_maxAllowedParticles)
    {
        m_maxParticles = c_maxAllowedParticles;
        GFX_WARN("Attempted to create ParticleSystem with %d particles, max allowed particles is %d. Using max allowed.", maxParticles, c_maxAllowedParticles);
    }
    else
    {
        m_maxParticles = maxParticles;
    }
}

// Resets and relaunches the particle as a new one.
void ParticleSystem::launchParticle(int i)
{
    glm::vec3 dirrr = glm::vec3(0);
    switch (m_cfg.volume)
    {
    case insideCirle:
        if (m_cfg.worldSpace)   m_data.pos[i] = m_gameObject->m_transform.getWorldPos();
        else                    m_data.pos[i] = glm::vec3(0,0,0);
        m_data.rot[i] =    glm::vec3(0, 0, OK::Util::random(0, glm::radians(360.0f)));
        m_data.scl[i] =    glm::vec3(m_cfg.startScale);
        
        dirrr = glm::normalize(glm::vec3(OK::Util::random(-1,1), OK::Util::random(-1,1), 0));
        m_data.vel[i] = dirrr * m_cfg.startSpeed;
        m_data.angVel[i] = glm::vec3(0,0, OK::Util::random(0, glm::radians(m_cfg.startAngleSpeed)));
        break;
    
    default:
        m_cfg = ParticleSystemConfiguration();
        GFX_ERROR("Invalid ParticleSystem configuration!");
        break;
    }

    m_data.color[i] = m_cfg.startColor;
    m_data.life[i] =   m_cfg.lifeTime;
}

void ParticleSystem::update(float deltaTime)
{
    deltaTime *= m_playbackSpeed;

    // Launch more particles?
    if (m_emitting)
    {
        m_cooldown -= deltaTime;
        if (m_cooldown <= 0)
        {
            m_cooldown =  1 / m_cfg.emissionsPerSec;
            float dt = deltaTime;
            do      // While still enough time, launch another particle this frame, reduce time.
            {
                launchParticle(m_oldestParticle);
                m_oldestParticle = (m_oldestParticle + 1) % m_maxParticles;
                if (m_highestIndex < m_maxParticles) 
                    m_highestIndex++;     
                dt -= m_cooldown;
            } while (dt >= m_cooldown);
        }
    }

    // Update particle attributes:
    m_particlesCount = 0;
    //Lifetime left:
    for (int i = 0; i < m_highestIndex; i++)
    {
        if (m_data.life[i] > 0)
        {
            m_data.life[i] -=  deltaTime;
            m_particlesCount++;
        }
    }
    GFX_DEBUG("Particles count: %d", m_particlesCount);

    // Velocities:
    for (int i = 0; i < m_highestIndex; i++)
    {
        m_data.vel[i] *= 1- m_cfg.drag * deltaTime;
        m_data.vel[i].y -= m_cfg.gravity * deltaTime;
    }
    for (int i = 0; i < m_highestIndex; i++)
        m_data.angVel[i] *= 1- m_cfg.angleDrag * deltaTime;
    
    // Position, rotation and scale:
    for (int i = 0; i < m_highestIndex; i++)
        m_data.pos[i] += m_data.vel[i] * deltaTime;

    for (int i = 0; i < m_highestIndex; i++)
        m_data.rot[i] += m_data.angVel[i] * deltaTime;
    
    for (int i = 0; i < m_highestIndex; i++)
        m_data.scl[i] = glm::vec3(m_cfg.startScale) * 
                 OK::Util::lerp(m_cfg.startScale, m_cfg.endScale, m_data.life[i] / m_cfg.lifeTime);
    
    // Color:
    for (int i = 0; i < m_highestIndex; i++)
        m_data.color[i] = OK::Util::lerpColor(m_cfg.startColor, m_cfg.endColor, m_data.life[i] / m_cfg.lifeTime);

    // Generate data to be sent to shader in the coming draw call:
    for (int i = 0; i < m_highestIndex; i++)
    {   
        //Scale, rotate, and translate particel accounting for origin:
        glm::mat4 rot = glm::mat4(1);
        rot = glm::translate(rot,  m_data.scl[i] * 0.5f + glm::vec3(m_size, 1) * 0.5f);
        rot *= glm::mat4_cast(glm::quat(m_data.rot[i]));
        rot = glm::translate(rot,  -m_data.scl[i]* 0.5f - glm::vec3(m_size, 1) * 0.5f);
        glm::mat4 scl = glm::scale(glm::mat4(1),     m_data.scl[i]);
        glm::mat4 trn = glm::translate(glm::mat4(1), m_data.pos[i]);
        m_shaderData.model[i] =  trn * rot * scl;
    }

    for (int i = 0; i < m_highestIndex; i++)
        m_shaderData.color[i] = m_data.color[i];
}

int ParticleSystem::count()
{   return m_particlesCount;    }

} // Namespace OK.