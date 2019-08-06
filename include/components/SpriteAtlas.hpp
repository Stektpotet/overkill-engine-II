#pragma once

#include "components/FlatGraphics.hpp"

namespace OK
{

class SpriteAtlas : public FlatGraphics
{
protected:
    void prepareGraphics() override;
    void update(float deltaTime) override;
    void configureShader(ShaderProgram shader) override;
    void draw() override;

public:
    SpriteAtlas(
        GameObject* gameObject,
        int id, 
        TextureAtlas atlas,
        
        int atlasIndex = 0 
    );

    //TODO: remove this property to the classes that use it
    //      the atlas should rather be used as an interface
    //      to look up anything & everything from the atlas
    //      rather than ONE sprite from the atlas at a time
    int m_atlasIndex;
    
    TextureAtlas m_atlas;
};

} // Namespace OK
