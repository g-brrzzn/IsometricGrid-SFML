#ifndef INFINITEGRID_H
#define INFINITEGRID_H

#include <unordered_map>
#include <vector>
#include <future>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "TextureManager.h"
#include "PerlinNoise.h"

struct ChunkCoord {
    int x, y;
    bool operator==(const ChunkCoord& o) const { return x == o.x && y == o.y; }
};

struct CoordHash {
    std::size_t operator()(const ChunkCoord& c) const noexcept {
        auto h1 = std::hash<long long>()(static_cast<long long>(c.x) << 32);
        auto h2 = std::hash<long long>()(static_cast<long long>(c.y));
        return h1 ^ (h2 >> 1);
    }
};

class InfiniteGrid {
public:
    InfiniteGrid(const TextureData& data);
    void render(sf::RenderWindow& window, const sf::View& view);
    void regenerate();

private:
    TextureData textures;
    PerlinNoise noiseGenerator;

    std::unordered_map<ChunkCoord,
        std::vector<std::vector<std::vector<cell>>>,
        CoordHash> chunkCache;

    std::unordered_map<ChunkCoord,
        std::future<std::vector<std::vector<std::vector<cell>>>>,
        CoordHash> generationJobs;

    std::vector<std::vector<std::vector<cell>>> generateChunk(int x, int y);
    std::vector<ChunkCoord> getVisibleChunks(const sf::View& view);
    int pickVariant(const std::vector<int>& options);
};

#endif