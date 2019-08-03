#pragma once
#include "components/Component.hpp"

namespace OK
{

class GraphicsComponent : public Component
{
private:
    static std::vector<std::shared_ptr<GraphicsComponent>>* GraphicsComponents;

protected:
    virtual void prepareGraphics() {}
    void update(float deltaTime) override {}     // Has to be pure virtual.
    inline void draw() override {}

public:
    static void PrepareGraphics();
    static void Draw();
    
    GraphicsComponent(GameObject* gameObject, int id);
};

} // Namespace OK