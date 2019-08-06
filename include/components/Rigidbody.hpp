#pragma once

#include "components/Component.hpp"

namespace OK
{
enum ForceMode 
{force, acceleration, velocityChange};

class Rigidbody : public Component
{
private:
    glm::vec3 m_acceleration;
    glm::vec3 m_angularAcceleration;
    float m_velocityMagnitude;          // Necessary because of float operations being inaccurate.
    float m_angularVelocityMagnitude;   // A ball bouncing will stop by itself even if no forces act on it.
                                        // Newton would not approve. We store the magnitude seperate and set it in update.
protected:
    void update(float deltaTime) override;

public:
    Rigidbody(
        GameObject* gameObject,
        int id, 
        float mass = 1,
        bool useGravity = false
    );

    glm::vec3 m_velocity;
    glm::vec3 m_angularVelocity;
    bool m_useGravity;
    float m_gravity;
    float m_mass;
    float m_drag;
    float m_angularDrag;

    void addForce(glm::vec3 force, ForceMode mode = force);
    void addTorque(glm::vec3 torque, ForceMode mode = force);

};

} // Namespace OK