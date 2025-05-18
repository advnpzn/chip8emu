#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({640, 400}), "Chip8 Emulator");
    window.setFramerateLimit(144);


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Cyan);
        window.display();
    }

    return 0;
}