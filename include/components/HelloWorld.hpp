#pragma once
#include <string>
#include "components/Component.hpp"
#include <gfx.h>

namespace OK
{

class HelloWorld : public Component
{
private:
    const int c_maxSpaces = 40;
    const float c_timeBetweenMoves = 0.05f;
    int m_spaces = 0;
    float m_timeLeft = c_timeBetweenMoves;
    bool m_reverse = false;
public:
    HelloWorld(GameObject* gameObject);
    void update(float deltatTime);
    void draw();
};

} // namespace OK
