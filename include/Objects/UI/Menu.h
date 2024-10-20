#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Objects/UI/Button.h"

// MenuItem class for each item in the dropdown menu
class MenuItem {
private:
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> onClick;

public:
    // Constructor for menu item
    MenuItem(const sf::Font& font, const std::string& label, const sf::Vector2f& size, const sf::Vector2f& position, std::function<void()> clickAction)
        : onClick(std::move(clickAction)) {
        shape.setSize(size);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);
        text.setPosition(
            position.x + (size.x - text.getGlobalBounds().width) / 2,
            position.y + (size.y - text.getGlobalBounds().height) / 2
        );
    }

    // Render the menu item
    void render(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    // Check for mouse hover
    bool isHovered(const sf::Vector2i& mousePosition) const {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
    }

    // Execute click action
    void click() const {
        if (onClick) {
            onClick();
        }
    }

    // Set the background color for hover effect
    void setHover(bool hover) {
        shape.setFillColor(hover ? sf::Color::Cyan : sf::Color::Blue);
    }
};

// DropdownMenu class for managing multiple menu items
class DropdownMenu {
private:
    sf::RectangleShape mainShape;
    sf::Text titleText;
    sf::Font font;
    std::vector<MenuItem> items;
    bool expanded = false;

public:
    // Constructor for dropdown menu
    DropdownMenu(const std::string& title, const sf::Font& font, const sf::Vector2f& size, const sf::Vector2f& position)
        : font(font) {
        mainShape.setSize(size);
        mainShape.setFillColor(sf::Color(50, 50, 50));
        mainShape.setPosition(position);

        titleText.setFont(font);
        titleText.setString(title);
        titleText.setCharacterSize(20);
        titleText.setFillColor(sf::Color::White);
        titleText.setPosition(
            position.x + 10,
            position.y + (size.y - titleText.getGlobalBounds().height) / 2
        );
    }

    // Add a menu item to the dropdown
    void addMenuItem(const std::string& label, std::function<void()> onClick) {
        float yOffset = 50.0f + (items.size() * 40.0f);
        items.emplace_back(font, label, sf::Vector2f(mainShape.getSize().x, 30), sf::Vector2f(mainShape.getPosition().x, mainShape.getPosition().y + yOffset), onClick);
    }

    // Update the dropdown state based on mouse position
    void update(const sf::Vector2i& mousePosition) {
        if (mainShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            expanded = true;
        } else {
            expanded = false;
        }

        for (auto& item : items) {
            if (expanded && item.isHovered(mousePosition)) {
                item.setHover(true);
            } else {
                item.setHover(false);
            }
        }
    }

    // Handle mouse click events
    void handleClick(const sf::Vector2i& mousePosition) {
        if (expanded) {
            for (auto& item : items) {
                if (item.isHovered(mousePosition)) {
                    item.click();
                    break;
                }
            }
        }
    }

    // Render the dropdown menu
    void render(sf::RenderWindow& window) {
        window.draw(mainShape);
        window.draw(titleText);

        if (expanded) {
            for (auto& item : items) {
                item.render(window);
            }
        }
    }
};

#endif // MENU_H
