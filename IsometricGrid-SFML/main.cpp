#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "TextureManager.h"
#include "Grid.h"

void updateCamera(sf::View& view, float dt) {
    const float cameraSpeed = 1000.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        view.move({ 0.f, -cameraSpeed * dt });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        view.move({ 0.f, cameraSpeed * dt });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        view.move({ -cameraSpeed * dt, 0.f });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        view.move({ cameraSpeed * dt, 0.f });
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), GAME_TITLE);
    //window.setFramerateLimit(60);

    TextureData texturedata = loadTextures();
    auto grid = generateGrid3D(texturedata);
    sf::View view(sf::FloatRect({ WORLD_WIDTH/4, WORLD_HEIGHT/4 }, { float(WINDOW_WIDTH), float(WINDOW_HEIGHT) }));

    float fps = 0.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        fps = 1.f / dt;
        window.setTitle(std::string(GAME_TITLE) +
            " - FPS: " + std::to_string(static_cast<int>(fps)) +
            "  View center : " + std::to_string(static_cast<int>(view.getCenter().x)) +
            ", " + std::to_string(static_cast<int>(view.getCenter().y)));

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::R)
                    grid = generateGrid3D(texturedata);
            }
        }

        updateCamera(view, dt);

        window.setView(view);
        window.clear(sf::Color{ 20, 20, 60 });

        renderGrid3D(window, view, grid);

        window.display();
    }
    return 0;
}
