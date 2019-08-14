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
    inline glm::vec4 lerpColor(glm::vec4 a, glm::vec4 b, float t)
    {
        return glm::vec4(
                         lerp(a.x, b.x, t),
                         lerp(a.y, b.y, t),
                         lerp(a.z, b.z, t),
                         lerp(a.w, b.w, t)
                        );
    }

    float random(float min, float max);
    glm::vec2 randomInUnitCircle();
    glm::vec2 randomOnUnitCircle();
    glm::vec3 randomInUnitSphere();
    glm::vec3 randomOnUnitSphere();

    void printTransform(Transform t);
    void processError(int code, const char* description);
    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v);
    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v, bool const& flag0, bool const& flag1);
    glm::uint16 packTexCoords(glm::vec2 const& v);
}