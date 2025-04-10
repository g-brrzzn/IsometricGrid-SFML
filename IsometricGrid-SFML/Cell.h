#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <optional>

class cell {
public:
    int type;
    int layer; 
    std::optional<sf::Sprite> sprite;

    cell();

    void initialize(int cellType, const sf::Texture& texture, float scaleX, float scaleY,
        float cellScale, float posX, float posY, int layer);
    void setLayer(int layer);
};

#endif
