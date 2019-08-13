#pragma once

#include "../model/Mesh.hpp"
#include "core/GraphicsComponent.hpp"

class MeshRenderer : public Renderer
{
    Mesh<Vertex_Full> mesh;
public:

    MeshRenderer(Mesh<Vertex_Full> mesh) : GraphicaComponent{}
    {

    }

    public void draw() 
    {
        mesh.
    }
};