#pragma once

#include <initializer_list>
#include <vector>
#include <memory>
#include <cstring> // strcomp(), finding GameObjects.

#include "GameObject.hpp"
#include "components/Component.hpp"
#include "components/GraphicsComponent.hpp"

namespace OK
{

class Scene
{
    friend class GraphicsComponent;
public:
    static Scene* currentScene;
    static inline void Update(float deltaTime) { currentScene->update(deltaTime); }

public:
    Scene(const char* name, std::initializer_list<std::shared_ptr<GameObject>> gameObjects);

    std::shared_ptr<GameObject> makeGameObject(const char* name);
    std::shared_ptr<GameObject> getGameObject(const char* name);
    std::shared_ptr<GameObject> getGameObject(int ID);

    void prepareGraphics();
    void draw();

private:
    const char* m_name;
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    std::vector<std::shared_ptr<GraphicsComponent>> m_graphicsComponents;

    void update(float deltaTime);

};

}