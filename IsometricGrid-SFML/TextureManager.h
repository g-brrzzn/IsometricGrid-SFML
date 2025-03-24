#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.h"

struct TextureData {
    std::vector<sf::Texture> textures;
    float scaleX;
    float scaleY;
    float cellScale;
};

TextureData loadTextures();

#endif
