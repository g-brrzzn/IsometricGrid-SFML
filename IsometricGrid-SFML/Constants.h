#ifndef CONSTANTS_H
#define CONSTANTS_H

#define GAME_TITLE "IsometricGrid-SFML"
constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;
constexpr unsigned int WORLD_WIDTH = 1600 * 10;
constexpr unsigned int WORLD_HEIGHT = 1600 * 10;
constexpr unsigned int TEXTURE_SIZE = 32;
constexpr unsigned int CELL_SIZE = TEXTURE_SIZE * 2;
constexpr unsigned int GRID_ROWS = (WORLD_HEIGHT + CELL_SIZE - 1) / CELL_SIZE;
constexpr unsigned int GRID_COLS = (WORLD_WIDTH + CELL_SIZE - 1) / CELL_SIZE;
constexpr unsigned int GRID_LAYERS = 3;         
constexpr unsigned int CELL_HEIGHT = 16;        
#endif
