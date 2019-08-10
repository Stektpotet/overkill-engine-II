#pragma once

#include "components/core/FlatGraphics.hpp"

namespace OK
{

class [[deprecated("Generalized and abstracted away differences in sprites, use Sprite instead")]] 
SpriteAtlas : public FlatGraphics
{
protected:
    void prepareGraphics() override;
    void update(float deltaTime) override;
    void configureShader(ShaderProgram shader) override;
    void draw() override;

public:
    SpriteAtlas(
        Texture2DArray atlas,
        int atlasIndex = 0 
    );

    //TODO: remove this property to the classes that use it
    //      the atlas should rather be used as an interface
    //      to look up anything & everything from the atlas
    //      rather than ONE sprite from the atlas at a time
    int m_atlasIndex;
    
    Texture2DArray m_atlas;
};

} // Namespace OK
