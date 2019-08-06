#pragma once
#include "Transform.hpp"
#include <glm/glm.hpp>
#include <gfx.h>


namespace OK::Util
{
    const float PI = 3.14159;
    const float Deg2Rad = (1.0f / 180.0f) * PI;
    const float Rad2Deg = (1.0f / PI) * 180.0f;

    void printTransform(Transform t);
    void processError(int code, const char* description);
    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v);
    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v, bool const& flag0, bool const& flag1);
    glm::uint16 packTexCoords(glm::vec2 const& v);
}