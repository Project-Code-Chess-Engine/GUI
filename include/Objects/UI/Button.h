#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class Button {
private:
    sf::RectangleShape shape; // Rectangle shape for the button
    sf::Text text;           // Text to be displayed on the button
    std::function<void()> onClick; // Action to be performed on click
    bool hovered;            // State to track hover effect

public:
    // Constructor
    Button(const sf::Font& font, const std::string& label, const sf::Vector2f& size, const sf::Vector2f& position, std::function<void()> clickAction)
        : onClick(std::move(clickAction)), hovered(false) {
        // Set up the button's shape
        shape.setSize(size);
        shape.setFillColor(sf::Color::Blue); // Default button color
        shape.setPosition(position);

        // Set up the button's text
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(
            position.x + (size.x - text.getGlobalBounds().width) / 2,
            position.y + (size.y - text.getGlobalBounds().height) / 2
        );
    }

    // Render the button
    void render(sf::RenderWindow& window) {
        window.draw(shape); // Draw the button shape
        window.draw(text);  // Draw the button text
    }

    // Handle hover effects
    void handleHover(const sf::Vector2i& mousePosition) {
        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            if (!hovered) {
                shape.setFillColor(sf::Color::Cyan); // Change color on hover
                hovered = true;
            }
        } else {
            if (hovered) {
                shape.setFillColor(sf::Color::Blue); // Revert color when not hovered
                hovered = false;
            }
        }
    }

    // Check if the button is clicked
    bool isClicked(const sf::Vector2i& mousePosition) const {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
    }

    // Execute the click action
    void click() const {
        if (onClick) {
            onClick(); // Call the assigned action
        }
    }
};

#endif // BUTTON_H
