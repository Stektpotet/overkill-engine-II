#include "components/GraphicsComponent.hpp"

namespace OK
{
    std::vector<std::shared_ptr<GraphicsComponent>>* GraphicsComponent::GraphicsComponents = nullptr;



// Static functions:
    void GraphicsComponent::PrepareGraphics()
    {
        if (GraphicsComponents == nullptr)
        { return; }

        GFX_DEBUG("Running graphics setup all %d components->..", GraphicsComponents->size());
        for (int i = 0; i < GraphicsComponents->size(); i++)
        {
            GraphicsComponents->at(i)->prepareGraphics();
        }
    }
   
    void GraphicsComponent::Draw() 
    {
        if (GraphicsComponents == nullptr)
        { return; }

        //GFX_DEBUG("Drawing all %d components->..", Components->size());
        for (int i = 0; i < GraphicsComponents->size(); i++)
        {
            GraphicsComponents->at(i)->draw();
        }
    }

// Non-static funcions:
    GraphicsComponent::GraphicsComponent(GameObject* gameObject, int id) : Component(gameObject, id)
    {
        if (GraphicsComponents == nullptr)
        {
            GraphicsComponents = new std::vector<std::shared_ptr<GraphicsComponent>>();
        }
        GraphicsComponents->push_back(std::shared_ptr<GraphicsComponent>(this));
    }

} // Namespace OK