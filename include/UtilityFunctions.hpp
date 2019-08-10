#pragma once
#include "Transform.hpp"
#include <glm/glm.hpp>
#include <gfx.h>


namespace OK::Util
{
    void printTransform(Transform t);
    void processError(int code, const char* description);
    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v);
    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v, bool const& flag0, bool const& flag1);
    glm::uint16 packTexCoords(glm::vec2 const& v);
}