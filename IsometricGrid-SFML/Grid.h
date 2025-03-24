#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Cell.h"
#include "TextureManager.h"

std::vector<std::vector<cell>> generateGrid(const TextureData& textureData);
void renderGrid(sf::RenderWindow& window, const sf::View& view, const std::vector<std::vector<cell>>& grid);

#endif
