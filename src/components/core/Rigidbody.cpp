#include "components/core/Rigidbody.hpp"

namespace OK
{
    Rigidbody::Rigidbody(
        bool useGravity, 
        float mass) :
        Component (),
        m_useGravity{useGravity}
        {
            m_velocity = glm::vec3(0);
            m_angularVelocity = glm::vec3(0);
            m_acceleration = glm::vec3(0);
            m_angularAcceleration = glm::vec3(0);
            m_gravity = -3;
            m_drag = 0;
            m_angularDrag = 0;
        }

    void Rigidbody::update(float deltaTime)
    {
        // Add other forces:
        if(m_useGravity)
            m_acceleration.y += m_gravity;

        // Alternative drag: 
        // https://en.wikipedia.org/wiki/Drag_equation:
        //m_acceleration *= (float)(0.5f * std::pow(glm::length(m_velocity), 2) * m_drag) / m_mass;
        //m_angularAcceleration *= (float)(0.5f * std::pow(glm::length(m_angularVelocity), 2) * m_drag) / m_mass;

        // Apply translation.
        m_velocity += m_acceleration;
        m_velocity *= 1 - m_drag * glm::length(m_velocity);
        m_gameObject->m_transform.position += m_velocity * deltaTime;
        
        // Apply rotation:
        m_angularVelocity += m_angularAcceleration;
        m_angularVelocity *= 1 - m_angularDrag * glm::length(m_angularVelocity) * deltaTime;
        m_gameObject->m_transform.rotation = m_gameObject->m_transform.rotation * glm::quat(m_angularVelocity * deltaTime);

        // Reset acceleration so we are ready to gather accelerations the next frame.
        m_acceleration = glm::vec3(0);
        m_angularAcceleration = glm::vec3(0);
    }

    void Rigidbody::addForce(glm::vec3 force, ForceMode mode)
    {
        if (mode == ForceMode::force)
            m_acceleration += force / m_mass;
        else if (mode == ForceMode::acceleration)
            m_acceleration += force;
        else if (mode == ForceMode::velocityChange)
        {
            float mag = glm::length(m_velocity);
            m_velocity = force;
            m_velocity = glm::normalize(m_velocity) * mag;
            //GFX_DEBUG("Magnitude: %.2f", mag);
        }
    }

    void Rigidbody::addTorque(glm::vec3 torque, ForceMode mode)
    {
        if (mode == ForceMode::force)
            m_angularAcceleration += torque / m_mass;
        else if (mode == ForceMode::acceleration)
            m_angularAcceleration += torque;
        else if (mode == ForceMode::velocityChange)
        {
            // float mag = glm::length(m_angvelocity);
            m_angularVelocity = torque;
           // m_angveloci
        }
    }

} // Namespace OK