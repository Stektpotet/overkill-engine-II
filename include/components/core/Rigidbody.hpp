#pragma once

#include "components/core/Component.hpp"

namespace OK
{
enum ForceMode 
{force, acceleration, velocityChange};

class Rigidbody : public Component
{
private:
    glm::vec3 m_acceleration;
    glm::vec3 m_angularAcceleration;

protected:
    void update(float deltaTime) override;

public:
    Rigidbody(
        bool useGravity = false,
        float mass = 1
    );

    glm::vec3 m_velocity;           // Note: never update velocities directly, 
    glm::vec3 m_angularVelocity;    // only set velocities to its initial value.
    bool m_useGravity;              // When doing updates on velocity often, use forces instead
    float m_gravity;                // to ensure the magnitude of the velocity doesn't shrink.
    float m_mass;
    float m_drag;
    float m_angularDrag;

    void addForce(glm::vec3 force, ForceMode mode = force);
    void addTorque(glm::vec3 torque, ForceMode mode = force);

};

} // Namespace OK