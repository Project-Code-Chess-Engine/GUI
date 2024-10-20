#ifndef PANEL_H
#define PANEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Objects/UI/Button.h"

// Panel class for movable and resizable UI sections
class Panel {
private:
    sf::RectangleShape panelShape;
    sf::Vector2f dragOffset;
    bool dragging = false;
    bool resizing = false;
    bool hover = false;

    sf::RectangleShape resizeHandle;
    sf::Vector2f resizeOffset;

public:
    // Constructor
    Panel(const sf::Vector2f& size, const sf::Vector2f& position) {
        // Initialize panel shape
        panelShape.setSize(size);
        panelShape.setFillColor(sf::Color(70, 70, 70));
        panelShape.setPosition(position);
        panelShape.setOutlineColor(sf::Color::White);
        panelShape.setOutlineThickness(2.0f);

        // Initialize resize handle
        resizeHandle.setSize(sf::Vector2f(10.0f, 10.0f));
        resizeHandle.setFillColor(sf::Color::White);
        updateResizeHandle();
    }

    // Update the position of the resize handle based on the panel's size and position
    void updateResizeHandle() {
        sf::Vector2f panelSize = panelShape.getSize();
        sf::Vector2f panelPosition = panelShape.getPosition();
        resizeHandle.setPosition(panelPosition.x + panelSize.x - resizeHandle.getSize().x, panelPosition.y + panelSize.y - resizeHandle.getSize().y);
    }

    // Update method for handling dragging and resizing
    void update(const sf::Vector2i& mousePosition, bool isMousePressed) {
        sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        
        // Handle dragging
        if (dragging) {
            if (isMousePressed) {
                panelShape.setPosition(mousePosF - dragOffset);
                updateResizeHandle();
            } else {
                dragging = false;
            }
        }
        // Handle resizing
        else if (resizing) {
            if (isMousePressed) {
                sf::Vector2f newSize = mousePosF - panelShape.getPosition() + resizeOffset;
                newSize.x = std::max(newSize.x, 50.0f);
                newSize.y = std::max(newSize.y, 50.0f);
                panelShape.setSize(newSize);
                updateResizeHandle();
            } else {
                resizing = false;
            }
        }
        // Check if the mouse is over the resize handle
        else if (resizeHandle.getGlobalBounds().contains(mousePosF)) {
            if (isMousePressed) {
                resizing = true;
                resizeOffset = resizeHandle.getPosition() - mousePosF;
            }
        }
        // Check if the mouse is over the panel for dragging
        else if (panelShape.getGlobalBounds().contains(mousePosF)) {
            if (isMousePressed) {
                dragging = true;
                dragOffset = mousePosF - panelShape.getPosition();
            }
        }
    }

    // Render the panel and its components
    void render(sf::RenderWindow& window) {
        window.draw(panelShape);
        window.draw(resizeHandle);
    }

    // Change the panel's color based on hover state
    void handleHover(const sf::Vector2i& mousePosition) {
        if (panelShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            if (!hover) {
                panelShape.setFillColor(sf::Color(90, 90, 90));
                hover = true;
            }
        } else {
            if (hover) {
                panelShape.setFillColor(sf::Color(70, 70, 70));
                hover = false;
            }
        }
    }
};

#endif // PANEL_H
