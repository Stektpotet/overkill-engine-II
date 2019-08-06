#include "components/Rigidbody.hpp"

namespace OK
{
    Rigidbody::Rigidbody(
        GameObject* gameObject,
        int id, 
        float mass,
        bool useGravity) : 
        Component (gameObject, id),
        m_useGravity{useGravity}
        {
            m_velocityMagnitude = 0;
            m_angularVelocityMagnitude = 0;
            m_velocity = glm::vec3(0);
            m_angularVelocity = glm::vec3(0);
            m_acceleration = glm::vec3(0);
            m_gravity = -10;
            m_drag = 0;
            m_angularDrag = 0;
        }

    void Rigidbody::update(float deltaTime)
    {
        // Add other forces:
        if(m_useGravity)
            m_acceleration.y += m_gravity;

        // https://en.wikipedia.org/wiki/Drag_equation:
        //m_acceleration *= (float)(0.5f * std::pow(glm::length(m_velocity), 2) * m_drag) / m_mass;
        //m_angularAcceleration *= (float)(0.5f * std::pow(glm::length(m_angularVelocity), 2) * m_drag) / m_mass;

        // Apply translation.
        m_velocity += m_acceleration;
        m_velocity *= 1 - m_drag * glm::length(m_velocity) * deltaTime;
        m_gameObject->m_transform.position += m_velocity * deltaTime;
        
        // Apply rotation:
        m_angularVelocity += m_angularAcceleration;
        m_angularVelocity *= 1 - m_angularDrag * glm::length(m_angularVelocity) * deltaTime;
        //m_gameObject->m_transform.rotation = m_gameObject->m_transform.rotation * glm::quat(m_angularVelocity) * deltaTime;
        // Getting rotation being nan because of this line, not sure why. TODO: fix.

        // Reset acceleration so we are ready to gather accelerations the next frame.
        m_acceleration = glm::vec3(0);
        m_angularAcceleration = glm::vec3(0);
    }

    void Rigidbody::addForce(glm::vec3 force, ForceMode mode)
    {
        if (mode == ForceMode::force)
            m_acceleration += force / m_mass;
        else if (mode == ForceMode::velocityChange)
            m_acceleration += force;
        else if (mode == ForceMode::acceleration)
        {
            //m_velocityMagnitude =  // Todo: fix 
            m_velocity = force;
        }
    }

    void Rigidbody::addTorque(glm::vec3 torque, ForceMode mode)
    {
        if (mode == ForceMode::force)
            m_angularAcceleration += torque / m_mass;
        else if (mode == ForceMode::velocityChange)
            m_angularAcceleration += torque;
        else if (mode == ForceMode::acceleration)
        {
            //m_angularVelocityMagnitude =  // Todo: fix 
            m_angularVelocity = torque;
        }
    }

} // Namespace OK