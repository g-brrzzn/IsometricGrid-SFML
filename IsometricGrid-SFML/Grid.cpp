#include "Grid.h"
#include "Constants.h"
#include "PerlinNoise.h"
#include <random>
#include <algorithm>
#include <cmath>
#include <chrono>

std::mt19937 gen(std::random_device{}());

int randomVariant(const std::vector<int>& options) {
    std::uniform_int_distribution<int> dist(0, static_cast<int>(options.size()) - 1);
    return options[dist(gen)];
}

std::vector<std::vector<std::vector<cell>>> generateGrid3D(const TextureData& textureData) {
    std::vector<std::vector<std::vector<cell>>> grid(
        GRID_LAYERS,
        std::vector<std::vector<cell>>(
            GRID_ROWS,
            std::vector<cell>(GRID_COLS)
        )
    );

    PerlinNoise perlin(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

    double frequency = 0.05;

    const double waterThreshold = 0.45;
    const double dirtThreshold = 0.5;

    for (unsigned int row = 0; row < GRID_ROWS; ++row) {
        for (unsigned int col = 0; col < GRID_COLS; ++col) {
            double noiseVal = perlin.noise(col * frequency, row * frequency, 0.0);
            double f = std::pow(noiseVal, 1.2);
            int desiredHeight = std::max(1, static_cast<int>(std::round(f * GRID_LAYERS)));

            for (unsigned int layer = 0; layer < GRID_LAYERS; ++layer) {
                if (layer < static_cast<unsigned int>(desiredHeight)) {
                    int chosenTextureIndex = 0;
                    if (layer == static_cast<unsigned int>(desiredHeight) - 1) {
                        if (f < waterThreshold) {
                            chosenTextureIndex = randomVariant({ 7, 8, 9 });
                        }
                        else if (f < dirtThreshold) {
                            chosenTextureIndex = randomVariant({ 4, 5, 6 });
                        }
                        else {
                            chosenTextureIndex = randomVariant({ 1, 2, 3 });
                        }
                    }
                    else {
                        chosenTextureIndex = randomVariant({ 4, 5, 6 });
                    }

                    int posX = (col - row) * CELL_SIZE / 2;
                    int posY = (col + row) * CELL_SIZE / 4 - layer * CELL_HEIGHT;

                    grid[layer][row][col].initialize(chosenTextureIndex, textureData.textures[chosenTextureIndex],
                        textureData.scaleX, textureData.scaleY, textureData.cellScale,
                        posX, posY, layer);
                }
            }
        }
    }
    return grid;
}

void renderGrid3D(sf::RenderWindow& window, const sf::View& view,
    const std::vector<std::vector<std::vector<cell>>>& grid) {
    sf::FloatRect viewRect({ view.getCenter().x - view.getSize().x / 2.f,
                             view.getCenter().y - view.getSize().y / 2.f },
        { view.getSize().x, view.getSize().y });

    for (unsigned int layer = 0; layer < grid.size(); ++layer) {
        for (unsigned int row = 0; row < grid[layer].size(); ++row) {
            for (unsigned int col = 0; col < grid[layer][row].size(); ++col) {
                int posX = (col - row) * CELL_SIZE / 2;
                int posY = (col + row) * CELL_SIZE / 4 - layer * CELL_HEIGHT;

                if (posX - viewRect.position.x + CELL_SIZE > 0 &&
                    posX - viewRect.position.x < viewRect.size.x &&
                    posY - viewRect.position.y + CELL_SIZE > 0 &&
                    posY - viewRect.position.y < viewRect.size.y) {

                    if (grid[layer][row][col].sprite)
                        window.draw(*grid[layer][row][col].sprite);
                }
            }
        }
    }
}
