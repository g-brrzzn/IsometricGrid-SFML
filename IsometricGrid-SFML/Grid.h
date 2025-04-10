#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cell.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

std::vector<std::vector<std::vector<cell>>> generateGrid3D(const TextureData& textureData);
void renderGrid3D(sf::RenderWindow& window, const sf::View& view,
    const std::vector<std::vector<std::vector<cell>>>& grid);

#endif
