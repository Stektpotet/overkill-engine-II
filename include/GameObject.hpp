#pragma once
#include <string>
#include <vector>
#include <algorithm>        // Find() in vector.
#include "Transform.hpp"
#include "Component.hpp"
#include <gfx.h>

namespace OK
{

class GameObject
{
private:
    Transform m_trasform;
    std::vector<int> m_components;
    std::string m_name;

    inline bool hasComponentWithID(int componentID);

public:
    GameObject( std::string name = "GameObject", 
                glm::vec3 pos = glm::vec3(0,0,0), 
                glm::vec3 scl = glm::vec3(1,1,1),
                glm::quat rot = glm::quat(0,0,0,1));

    GameObject( std::string name = "GameObject", 
                Transform trans = { glm::vec3(0,0,0), 
                                    glm::vec3(1,1,1), 
                                    glm::quat(0,0,0,1)});

    bool addComponent(int componentID);         // Takes in the ID of an existing component and attempts to add it.
                                                // Can fail it it already has the component or the component already has a GameObject reference.
    bool removeComponent(int componentID);      // Removes the component so it is no longer assiciated with this GameObject.
                                                // NB! Does not destroy the component.
};

}