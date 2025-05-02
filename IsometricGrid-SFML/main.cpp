#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "TextureManager.h"
#include "InfiniteGrid.h"

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
    window.setVerticalSyncEnabled(true);

    TextureData tex = loadTextures();
    InfiniteGrid world(tex);
    sf::View view{ {0,0},
                {static_cast<float>(WINDOW_WIDTH),
                 static_cast<float>(WINDOW_HEIGHT)} };

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
                    world.regenerate();
            }
        }

        updateCamera(view, dt);
        window.setView(view);
        window.clear({ 20,20,60 });

        world.render(window, view);

        window.display();
    }
    return 0;
}
