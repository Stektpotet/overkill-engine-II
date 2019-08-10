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

std::shared_ptr<GameObject> Scene::getGameObject(const char* name)
{
    auto iterator = std::find_if(m_gameObjects.begin(), m_gameObjects.end(), 
                [name](std::shared_ptr<GameObject> g)
                {
                    return !std::strcmp(name, g->getName().data());
                }
            );
    if (iterator == m_gameObjects.end())
    {
        GFX_WARN("Searched for GameObject with name '%s', NOT FOUND!", name);
        return nullptr;
    }
    GFX_DEBUG("Searched for GameObject with name '%s', found.", name);
    return *iterator.base();
}

std::shared_ptr<GameObject> Scene::getGameObject(int ID)
{
        auto iterator = std::find_if(m_gameObjects.begin(), m_gameObjects.end(), 
                [ID](std::shared_ptr<GameObject> g)
                {
                    return ID == g->getID();
                }
            );
    if (iterator == m_gameObjects.end())
    {
        GFX_WARN("Searched for GameObject with ID '%d', NOT FOUND!", ID);
        return nullptr;
    }

    GFX_DEBUG("Searched for GameObject with ID '%d', found.", ID);
    return *iterator.base();
}




void Scene::update(float deltaTime)
{
    for (const auto& go : m_gameObjects)
        go->update(deltaTime);
}

void Scene::prepareGraphics()
{
    GFX_DEBUG("Running graphics setup all %d components->..", m_graphicsComponents.size());
    for (auto& comp : m_graphicsComponents)
    {
        comp->prepareGraphics();
    }
}

void Scene::draw()
{
    //GFX_DEBUG("Drawing all %d components->..", Components->size());
    for (auto& comp : m_graphicsComponents)
    {
        comp->draw();
    }
}

}