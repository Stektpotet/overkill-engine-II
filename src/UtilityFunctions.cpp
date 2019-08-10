#include "UtilityFunctions.hpp"

namespace OK::Util
{

    float random(float min, float max)
    {   
        GFX_DEBUG("Generatign random number between %.2f and %.2f:", min, max);
        int accuracy = 1000000;
        min *= accuracy;
        max *= accuracy;
        float result = ((std::rand() + (int)min) % (int)max) / (float)accuracy;
        GFX_DEBUG("Generated: %.4f ", result);
        return result;

    }

    void printTransform(Transform t)
    {
        glm::vec3 rot = glm::eulerAngles(t.rotation);
		GFX_DEBUG("Pos: %.2f \t%.2f \t%.2f \tRot: %.2f \t%.2f \t%.2f", 
        t.position.x, t.position.y, t.position.z, 
        glm::degrees(rot.x), 
        glm::degrees(rot.y), 
        glm::degrees(rot.z));
    }

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


