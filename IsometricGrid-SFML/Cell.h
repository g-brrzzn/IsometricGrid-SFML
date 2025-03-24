#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <optional>

struct cell {
    int type;
    std::optional<sf::Sprite> sprite;

    cell();
    void initialize(int cellType, const sf::Texture& texture, float scaleX, float scaleY, float cellScale, float posX, float posY);
};

#endif

