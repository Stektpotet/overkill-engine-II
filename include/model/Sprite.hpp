#pragma once

#include "Mesh.hpp"
#include "../graphics_internal/Texture.hpp"
namespace OK
{

struct SpriteVertex 
{
    glm::vec2 position;
    GLushort texcoords;
    static InterleavingVertexLayout InterleavingLayout()
    {
        return InterleavingVertexLayout{ {
                Attribute{ "position", 32, 4, GL_FLOAT },
                Attribute{ "texcoord", 2, 4, GL_UNSIGNED_SHORT, GL_TRUE },
        } };
    }
};

template <class TTexture>
class Sprite : public Mesh<SpriteVertex>
{
    template<typename T>
    friend class SpriteRenderer;
protected:
public:
    TTexture m_texture; //TODO: access modifiers
    Sprite(TTexture texture) : 
        Mesh<SpriteVertex>{{
            {
                SpriteVertex{{0,0}, 0x0000},
                SpriteVertex{{1,0}, 0xff00},
                SpriteVertex{{0,1}, 0xff00},
                SpriteVertex{{1,1}, 0xffff},
            },
            {
                0,1,2,
                2,1,3
            }
        }},
        m_texture{ texture }
    {
    }
};

using SpriteAtlased = Sprite<Texture2DArray>;

}