#include "components/HelloWorld.hpp"

namespace OK
{
HelloWorld::HelloWorld() : Component()
{}

void HelloWorld::update(float deltaTime)
{
    m_timeLeft -= deltaTime;
    if (m_timeLeft > 0)
    {
        return;
    }
    m_timeLeft = c_timeBetweenMoves;

    std::string text;
    if (m_reverse)
        m_spaces--;
    else
         m_spaces++;   

    if (m_spaces > c_maxSpaces)
        m_reverse = true;
    if (m_spaces == 0)
        m_reverse = false;

    for (int i = 0; i < m_spaces; i++)
        text += " ";
    text += "Hello World!!";

    GFX_INFO("%s", text.data());
}

} // namespace OK
