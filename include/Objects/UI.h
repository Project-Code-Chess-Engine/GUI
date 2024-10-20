#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <string>

// Button class for modular UI elements
class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> onClick;
    bool hovered = false;

public:
    // Constructor for button
    Button(const sf::Font& font, const std::string& label, const sf::Vector2f& size, const sf::Vector2f& position, std::function<void()> clickAction)
        : onClick(std::move(clickAction)) {
        shape.setSize(size);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);

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
        window.draw(shape);
        window.draw(text);
    }

    // Handle mouse hover effect
    void handleHover(const sf::Vector2i& mousePosition) {
        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            if (!hovered) {
                shape.setFillColor(sf::Color::Cyan);
                hovered = true;
            }
        } else {
            if (hovered) {
                shape.setFillColor(sf::Color::Blue);
                hovered = false;
            }
        }
    }

    // Check for click
    bool isClicked(const sf::Vector2i& mousePosition) const {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
    }

    // Execute click action
    void click() const {
        if (onClick) {
            onClick();
        }
    }
};

// UI class to manage the overall interface
class UI : public RenderObject {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text statusText;
    std::vector<Button> buttons;  // Store Button objects directly

public:
    // Constructor
    UI(sf::RenderWindow& win) : window(win) {
        // Load font
        if (!font.loadFromFile("assets/OpenSans-Regular.ttf")) {
            // Handle error (consider logging or throwing an exception)
        }

        // Initialize status text
        statusText.setFont(font);
        statusText.setCharacterSize(24);
        statusText.setFillColor(sf::Color::Black);
        statusText.setPosition(10, 10);

        // Initialize buttons with move semantics to avoid unnecessary copying
        buttons.emplace_back(Button(font, "Reset", sf::Vector2f(100, 50), sf::Vector2f(650, 100), [&]() {
            resetGame();
        }));

        buttons.emplace_back(Button(font, "Exit", sf::Vector2f(100, 50), sf::Vector2f(650, 170), [&]() {
            window.close();
        }));


        buttons.emplace_back(Button(font, "Chess.com", sf::Vector2f(100, 50), sf::Vector2f(650, 240), [&]() {
            openChessCom();
        }));

    }
    void openChessCom() {
        // Open the default web browser to Chess.com
        #ifdef _WIN32
            system("start https://www.chess.com");
        #elif __APPLE__
            system("open https://www.chess.com");
        #elif __linux__
            system("xdg-open https://www.chess.com");
        #endif
    }
    // Inherited update method (for interactive elements)
    void update() override {
        // For future interactive updates
    }

    // Inherited render method
    void render() override {
        window.draw(statusText); // Draw status text
        for (auto& button : buttons) {
            button.render(window); // Draw each button
        }
    }

    // Handle right-click on the chessboard, updating the status text
    void handleRightClick(int row, int col, const Piece& piece) {
        statusText.setString("Right clicked on piece at (" + std::to_string(row) + ", " + std::to_string(col) + ")");
    }

    // Handle mouse movement for hover effects
    void handleMouseHover(const sf::Vector2i& mousePosition) {
        for (auto& button : buttons) {
            button.handleHover(mousePosition);
        }
    }

    // Handle button clicks
    void handleMouseClick(const sf::Vector2i& mousePosition) {

        for (auto& button : buttons) {
            if (button.isClicked(mousePosition)) {
                cout<<"Clicked"<<endl;
                button.click();
            }
        }
    }

    // Reset the game
    void resetGame() {
        statusText.setString("Game reset!");
    }
};

#endif // UI_H
