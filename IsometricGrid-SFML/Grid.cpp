#include "Grid.h"
#include "Constants.h"
#include <random>
#include <algorithm>

std::mt19937 gen(std::random_device{}());
std::discrete_distribution<int> cellTypeDist({ 0.0, 0.25, 0.25, 0.5 });

std::vector<std::vector<cell>> generateGrid(const TextureData& textureData) {
    std::vector<std::vector<cell>> grid(GRID_ROWS, std::vector<cell>(GRID_COLS));

    for (unsigned int row = 0; row < GRID_ROWS; ++row) {
        for (unsigned int col = 0; col < GRID_COLS; ++col) {
            int cellType = cellTypeDist(gen);

            int posX = (col - row) * CELL_SIZE / 2;
            int posY = (col + row) * CELL_SIZE / 4;

            if (cellType >= 1) {
                grid[row][col].initialize(cellType, textureData.textures[cellType],
                    textureData.scaleX, textureData.scaleY,
                    textureData.cellScale, posX, posY);
            }
        }
    }
    return grid;
}


void renderGrid(sf::RenderWindow& window, const sf::View& view, const std::vector<std::vector<cell>>& grid) {
    sf::FloatRect viewRect(
        { view.getCenter().x - view.getSize().x / 2.f,
          view.getCenter().y - view.getSize().y / 2.f },
        { view.getSize().x, view.getSize().y }
    );

    //culling
    for (int row = 0; row < GRID_ROWS; ++row) {
        for (int col = 0; col < GRID_COLS; ++col) {
            
            int posX = (col - row) * CELL_SIZE / 2;
            int posY = (col + row) * CELL_SIZE / 4;

            
            if (posX - viewRect.position.x + CELL_SIZE > 0 &&  
                posX - viewRect.position.x < viewRect.size.x && 
                posY - viewRect.position.y + CELL_SIZE > 0 && 
                posY - viewRect.position.y < viewRect.size.y) {

             
                if (grid[row][col].sprite) {
                    window.draw(*grid[row][col].sprite);
                }
            }
        }
    }
}
