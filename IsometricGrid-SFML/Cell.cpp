#include "Cell.h"
#include <iostream>

cell::cell() : type(0), sprite(std::nullopt) {}

void cell::initialize(int cellType, const sf::Texture& texture, float scaleX, float scaleY, float cellScale, float posX, float posY) {
    type = cellType;
    if (type >= 1) {
        sprite.emplace(texture);
        sprite->setScale(sf::Vector2f(scaleX * cellScale, scaleY * cellScale));
        sprite->setPosition(sf::Vector2f(posX, posY));
    }
}
