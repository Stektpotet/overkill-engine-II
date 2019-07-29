#pragma once

#include <initializer_list>
#include <vector>
#include <memory>


#include "components/Component.hpp"
#include "GameObject.hpp"

namespace OK
{

class Scene
{
public:
    static Scene* currentScene;
    static inline void Update(float deltaTime) { currentScene->update(deltaTime); }

public:

    Scene(const char* name, std::initializer_list<std::shared_ptr<GameObject>> gameObjects);

    std::shared_ptr<GameObject> makeGameObject(const char* name);

private:
    const char* m_name;
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;

    void update(float deltaTime);

};

}