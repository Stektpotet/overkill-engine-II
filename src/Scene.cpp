#include "Scene.hpp"

namespace OK
{
Scene* Scene::currentScene;

Scene::Scene(
    const char * name,
    std::initializer_list<std::shared_ptr<GameObject>> gameObjects
) : m_name{ name }, m_gameObjects{ gameObjects }
{

}

std::shared_ptr<GameObject> Scene::makeGameObject(const char * name)
{
    return m_gameObjects.emplace_back(std::make_shared<GameObject>(name));
}

void Scene::update(float deltaTime)
{
    for (const auto& go : m_gameObjects)
        go->update(deltaTime);
}

}