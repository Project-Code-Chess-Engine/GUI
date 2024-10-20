#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Objects/UI/Button.h"

// Sidebar class to manage sidebar UI with animations
class Sidebar {
private:
    sf::RectangleShape shape;              // Shape of the sidebar
    std::vector<Button> buttons;           // List of buttons in the sidebar
    sf::Vector2f collapsedPosition;        // Position when sidebar is collapsed
    sf::Vector2f expandedPosition;         // Position when sidebar is expanded
    bool isExpanded;                       // State of the sidebar
    float animationSpeed;                  // Speed of sidebar animation

public:
    // Constructor
    Sidebar(const sf::Font& font, const sf::Vector2f& size, const sf::Vector2f& collapsedPos, const sf::Vector2f& expandedPos)
        : collapsedPosition(collapsedPos), expandedPosition(expandedPos), isExpanded(false), animationSpeed(300.0f) {
        shape.setSize(size);
        shape.setFillColor(sf::Color(30, 30, 30, 200)); // Semi-transparent gray
        shape.setPosition(collapsedPosition);
    }

    // Add a button to the sidebar
    void addButton(const std::string& label, const sf::Font& font, std::function<void()> onClick) {
        float yOffset = 60.0f * buttons.size() + 20.0f;
        buttons.emplace_back(font, label, sf::Vector2f(180, 40), sf::Vector2f(shape.getPosition().x + 10, shape.getPosition().y + yOffset), onClick);
    }

    // Update animation and state based on mouse position
    void update(const sf::Vector2i& mousePosition, float deltaTime) {
        // Expand or collapse sidebar based on mouse position
        bool shouldExpand = shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));

        if (shouldExpand && !isExpanded) {
            isExpanded = true;
        } else if (!shouldExpand && isExpanded) {
            isExpanded = false;
        }

        // Animate the sidebar movement
        animateSidebar(deltaTime);

        // Update buttons position and hover state
        for (auto& button : buttons) {
            button.handleHover(mousePosition);
        }
    }

    // Render the sidebar and its buttons
    void render(sf::RenderWindow& window) {
        window.draw(shape);
        for (auto& button : buttons) {
            button.render(window);
        }
    }

private:
    // Animation logic for sidebar movement
    void animateSidebar(float deltaTime) {
        sf::Vector2f targetPosition = isExpanded ? expandedPosition : collapsedPosition;
        sf::Vector2f currentPosition = shape.getPosition();
        sf::Vector2f direction = targetPosition - currentPosition;

        if (std::abs(direction.x) > 0.1f) {
            shape.move(direction * animationSpeed * deltaTime);
            // Update button positions based on sidebar movement
            for (auto& button : buttons) {
                sf::Vector2f newPosition = {shape.getPosition().x + 10, button.getShape().getPosition().y};
                button.setPosition(newPosition);
            }
        } else {
            shape.setPosition(targetPosition); // Snap to target position
        }
    }
};

#endif // SIDEBAR_H
