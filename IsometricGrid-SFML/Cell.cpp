#include "Cell.h"
#include <iostream>

cell::cell() : type(0), layer(0), sprite(std::nullopt) {}

void cell::initialize(int cellType, const sf::Texture& texture, float scaleX, float scaleY,
    float cellScale, float posX, float posY, int layer) {
    type = cellType;
    this->layer = layer;
    if (cellType >= 1) {
        sprite.emplace(texture);
        sprite->setScale(sf::Vector2f(scaleX * cellScale, scaleY * cellScale));
        sprite->setPosition(sf::Vector2f(posX, posY));
    }
}

void cell::setLayer(int layer) {
    this->layer = layer;
}
