#include "TextureManager.h"
#include <iostream>

TextureData loadTextures() {
    TextureData data;
    data.textures.resize(10);

    if (!data.textures[1].loadFromFile("tile1.png"))
        std::cerr << "Erro ao carregar tile1.png" << std::endl;
    if (!data.textures[2].loadFromFile("tile2.png"))
        std::cerr << "Erro ao carregar tile2.png" << std::endl;
    if (!data.textures[3].loadFromFile("tile3.png"))
        std::cerr << "Erro ao carregar tile3.png" << std::endl;

    if (!data.textures[4].loadFromFile("dirt1.png"))
        std::cerr << "Erro ao carregar dirt1.png" << std::endl;
    if (!data.textures[5].loadFromFile("dirt2.png"))
        std::cerr << "Erro ao carregar dirt2.png" << std::endl;
    if (!data.textures[6].loadFromFile("dirt3.png"))
        std::cerr << "Erro ao carregar dirt3.png" << std::endl;

    if (!data.textures[7].loadFromFile("water1.png"))
        std::cerr << "Erro ao carregar water1.png" << std::endl;
    if (!data.textures[8].loadFromFile("water2.png"))
        std::cerr << "Erro ao carregar water2.png" << std::endl;
    if (!data.textures[9].loadFromFile("water3.png"))
        std::cerr << "Erro ao carregar water3.png" << std::endl;

    sf::Vector2u textureSize = data.textures[1].getSize();
    data.scaleX = static_cast<float>(TEXTURE_SIZE) / textureSize.x;
    data.scaleY = static_cast<float>(TEXTURE_SIZE) / textureSize.y;
    data.cellScale = static_cast<float>(CELL_SIZE) / TEXTURE_SIZE;

    return data;
}
