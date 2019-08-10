#pragma once
#include <stdlib.h>
#include "Transform.hpp"
#include <glm/glm.hpp>
#include <gfx.h>


namespace OK::Util
{
    inline float lerp(float a, float b, float t)  // No std::lerp until c++20 :(
    {
        return a*t + (1-t)*b;
    }
    inline float slerp(float a, float b, float t)
    {
        t = 3*t*t + 2*t*t*t;    // 3x² - 2x³
        return a*t + (1-t)*b;
    }


    float random(float min, float max);
    void printTransform(Transform t);
    void processError(int code, const char* description);
    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v);
    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v, bool const& flag0, bool const& flag1);
    glm::uint16 packTexCoords(glm::vec2 const& v);
}