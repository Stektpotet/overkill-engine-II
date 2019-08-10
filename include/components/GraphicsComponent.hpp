#pragma once
#include "components/Component.hpp"

namespace OK
{
class GameObject;

class GraphicsComponent : public Component, public std::enable_shared_from_this<GraphicsComponent>
{
    friend class Scene;
protected:
    virtual void prepareGraphics() {}
    void onCreated() override;

public:
    
    GraphicsComponent();
};

} // Namespace OK