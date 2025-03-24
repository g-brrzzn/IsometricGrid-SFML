#include "TextureManager.h"
#include <iostream>

TextureData loadTextures() {
    TextureData data;
    data.textures.resize(4); // 0: empty

    if (!data.textures[1].loadFromFile("tile1.png"))
        std::cerr << "Erro ao carregar tile1.png" << std::endl;
    if (!data.textures[2].loadFromFile("tile2.png"))
        std::cerr << "Erro ao carregar tile2.png" << std::endl;
    if (!data.textures[3].loadFromFile("tile3.png"))
        std::cerr << "Erro ao carregar tile3.png" << std::endl;

    sf::Vector2u textureSize = data.textures[1].getSize();
    data.scaleX = static_cast<float>(TEXTURE_SIZE) / textureSize.x;
    data.scaleY = static_cast<float>(TEXTURE_SIZE) / textureSize.y;
    data.cellScale = static_cast<float>(CELL_SIZE) / TEXTURE_SIZE;

    return data;
}
