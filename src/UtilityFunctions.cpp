#include "UtilityFunctions.hpp"

namespace OK::Util
{

    void processError(int code, const char* description) 
    { GFX_ERROR("%s - %s", glewGetErrorString(code), description); }


    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v) {
        const auto DISCARD_MASK = 1023;
        const auto MAX = 511;

        float magnitude = glm::length(v);
        GLuint x =  GLuint(v.x * MAX) & DISCARD_MASK;
        GLuint y =  GLuint(v.y * MAX) & DISCARD_MASK;
        GLuint z =  GLuint(v.z * MAX) & DISCARD_MASK;

        return 0 | (z << 20) | (y << 10) | (x << 0);
    }
    glm::uint packSnorm10x3_2Rev(glm::vec3 const& v, bool const& flag0, bool const& flag1) {
        const auto DISCARD_MASK = 1023;
        const auto MAX = 511;

        float magnitude = glm::length(v);
        GLuint x = GLuint(v.x * MAX) & DISCARD_MASK;
        GLuint y = GLuint(v.y * MAX) & DISCARD_MASK;
        GLuint z = GLuint(v.z * MAX) & DISCARD_MASK;

        return flag0 << 31 | flag1 << 30 | (z << 20) | (y << 10) | (x << 0);
    }

    glm::uint16 packTexCoords(glm::vec2 const& v) {
        const auto DISCARD_MASK = 511;
        const auto MAX = 255;

        float magnitude = glm::length(v);
        GLuint x = GLuint(v.x * MAX) & DISCARD_MASK;
        GLuint y = GLuint(v.y * MAX) & DISCARD_MASK;

        return (y << 8) | (x << 0);
    }


}


