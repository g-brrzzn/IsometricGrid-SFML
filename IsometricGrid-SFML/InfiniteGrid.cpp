#include "InfiniteGrid.h"
#include "Constants.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <optional>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <cmath>
#include <random>

InfiniteGrid::InfiniteGrid(const TextureData& data)
    : textures(data),
    noiseGenerator(static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count()))
{
    chunkCache.reserve(256);
}

int InfiniteGrid::pickVariant(const std::vector<int>& options) {
    static std::mt19937 randomEngine(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(options.size()) - 1);
    return options[dist(randomEngine)];
}

std::vector<std::vector<std::vector<cell>>> InfiniteGrid::generateChunk(int chunkX, int chunkY) {
    int chunkSize = CHUNK_SIZE;
    std::vector<std::vector<std::vector<cell>>> chunk(
        GRID_LAYERS,
        std::vector<std::vector<cell>>(chunkSize, std::vector<cell>(chunkSize))
    );
    const double noiseFrequency = 0.04;
    const double waterThreshold = 0.45;
    const double dirtThreshold = 0.50;

    for (int localY = 0; localY < chunkSize; ++localY) {
        for (int localX = 0; localX < chunkSize; ++localX) {
            int globalX = chunkX * chunkSize + localX;
            int globalY = chunkY * chunkSize + localY;
            double noiseValue = noiseGenerator.noise(globalX * noiseFrequency, globalY * noiseFrequency, 0.0);
            double heightFactor = std::pow(noiseValue, 1.2);
            int layerCount = std::max(1, static_cast<int>(std::round(heightFactor * GRID_LAYERS)));

            for (unsigned layerIndex = 0; layerIndex < GRID_LAYERS; ++layerIndex) {
                if (layerIndex < static_cast<unsigned>(layerCount)) {
                    int textureIndex;
                    if (layerIndex == static_cast<unsigned>(layerCount) - 1) {
                        if (heightFactor < waterThreshold) {
                            textureIndex = pickVariant({ 7, 8, 9 });
                        }
                        else if (heightFactor < dirtThreshold) {
                            textureIndex = pickVariant({ 4, 5, 6 });
                        }
                        else {
                            textureIndex = pickVariant({ 1, 2, 3 });
                        }
                    }
                    else {
                        textureIndex = pickVariant({ 4, 5, 6 });
                    }

                    float worldX = (globalX - globalY) * CELL_SIZE * 0.5f;
                    float worldY = (globalX + globalY) * CELL_SIZE * 0.25f - layerIndex * CELL_HEIGHT;

                    chunk[layerIndex][localY][localX].initialize(
                        textureIndex, textures.textures[textureIndex],
                        textures.scaleX, textures.scaleY, textures.cellScale,
                        worldX, worldY, layerIndex
                    );
                }
            }
        }
    }
    return chunk;
}

std::vector<ChunkCoord> InfiniteGrid::getVisibleChunks(const sf::View& view) {
    sf::Rect<float> viewBounds(view.getCenter() - view.getSize() * 0.5f, view.getSize());
    viewBounds.position.x -= CELL_SIZE;
    viewBounds.position.y -= CELL_SIZE;
    viewBounds.size.x += 2 * CELL_SIZE;
    viewBounds.size.y += 2 * CELL_SIZE;

    std::vector<sf::Vector2f> corners;
    corners.reserve(4);
    corners.emplace_back(viewBounds.position.x, viewBounds.position.y);
    corners.emplace_back(viewBounds.position.x + viewBounds.size.x, viewBounds.position.y);
    corners.emplace_back(viewBounds.position.x, viewBounds.position.y + viewBounds.size.y);
    corners.emplace_back(viewBounds.position.x + viewBounds.size.x, viewBounds.position.y + viewBounds.size.y);

    float minTileX = 1e9f, minTileY = 1e9f, maxTileX = -1e9f, maxTileY = -1e9f;
    const float invCellQuarter = 1.f / (CELL_SIZE * 0.25f);
    const float invCellHalf = 1.f / (CELL_SIZE * 0.5f);

    for (auto& point : corners) {
        float screenX = point.x;
        float screenY = point.y;
        float tileX = (screenY * invCellQuarter + screenX * invCellHalf) * 0.5f;
        float tileY = (screenY * invCellQuarter - screenX * invCellHalf) * 0.5f;
        minTileX = std::min(minTileX, tileX);
        maxTileX = std::max(maxTileX, tileX);
        minTileY = std::min(minTileY, tileY);
        maxTileY = std::max(maxTileY, tileY);
    }

    int startX = static_cast<int>(std::floor(minTileX / CHUNK_SIZE));
    int endX = static_cast<int>(std::floor(maxTileX / CHUNK_SIZE));
    int startY = static_cast<int>(std::floor(minTileY / CHUNK_SIZE));
    int endY = static_cast<int>(std::floor(maxTileY / CHUNK_SIZE));

    std::vector<ChunkCoord> visibleChunks;
    visibleChunks.reserve((endX - startX + 1) * (endY - startY + 1));

    for (int x = startX; x <= endX; ++x) {
        for (int y = startY; y <= endY; ++y) {
            visibleChunks.emplace_back(ChunkCoord{ x, y });
        }
    }

    return visibleChunks;
}

void InfiniteGrid::render(sf::RenderWindow& window, const sf::View& view) {
    sf::Rect<float> viewBounds(view.getCenter() - view.getSize() * 0.5f, view.getSize());
    auto visibleChunkCoords = getVisibleChunks(view);
    std::vector<sf::Sprite*> spritesToDraw;
    spritesToDraw.reserve(visibleChunkCoords.size() * CHUNK_SIZE * CHUNK_SIZE);

    for (auto& chunkCoord : visibleChunkCoords) {
        if (chunkCache.find(chunkCoord) == chunkCache.end() &&
            generationJobs.find(chunkCoord) == generationJobs.end()) {
            generationJobs[chunkCoord] = std::async(std::launch::async,
                &InfiniteGrid::generateChunk, this, chunkCoord.x, chunkCoord.y);
        }

        auto jobIt = generationJobs.find(chunkCoord);
        if (jobIt != generationJobs.end() &&
            jobIt->second.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            chunkCache[chunkCoord] = jobIt->second.get();
            generationJobs.erase(jobIt);
        }

        auto cacheIt = chunkCache.find(chunkCoord);
        if (cacheIt == chunkCache.end()) continue;
        auto& chunkData = cacheIt->second;

        for (unsigned layerIndex = 0; layerIndex < GRID_LAYERS; ++layerIndex) {
            for (int localY = 0; localY < CHUNK_SIZE; ++localY) {
                for (int localX = 0; localX < CHUNK_SIZE; ++localX) {
                    auto& spriteOpt = chunkData[layerIndex][localY][localX].sprite;
                    if (!spriteOpt) continue;
                    sf::Sprite& sprite = *spriteOpt;
                    if (!viewBounds.findIntersection(sprite.getGlobalBounds()).has_value()) continue;
                    spritesToDraw.push_back(&sprite);
                }
            }
        }
    }

    for (auto sprite : spritesToDraw) {
        window.draw(*sprite);
    }
}

void InfiniteGrid::regenerate() {
    chunkCache.clear();
    generationJobs.clear();
}
