#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "components/ParticleSystem.hpp"

namespace OK
{

class ParticleSystemSprite : public ParticleSystem
{
private:
    Texture2D m_texture;

protected:
    void prepareGraphics() override;
    void draw() override;

public:
    ParticleSystemSprite(Texture2D texture, 
                         int maxParticles, 
                         ParticleSystemConfiguration config
                        );
};


} // Namespace.