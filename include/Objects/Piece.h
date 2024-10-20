#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

// Piece class to represent a chess piece
class Piece {
private:
    sf::Sprite sprite;                         // Sprite for the piece (image)
    std::shared_ptr<sf::Texture> texture;      // Shared texture to reduce memory overhead by sharing textures
    bool active = false;                       // Whether the piece is active on the board
    std::string type;                          // Type of the piece (e.g., "pawn", "knight", etc.)
    sf::Color color;                           // Color of the piece (white or black)

public:
    // Default constructor (inactive piece)
    Piece() = default;

    // Constructor that sets the type, color, and lazily loads texture
    Piece(const std::string& pieceType, const sf::Color& pieceColor)
        : type(pieceType), color(pieceColor), active(true) {
        loadTexture();
    }

    // Move constructor for efficient transfers
    Piece(Piece&& other) noexcept
        : sprite(std::move(other.sprite)), texture(std::move(other.texture)),
          active(other.active), type(std::move(other.type)), color(other.color) {}

    // Move assignment operator
    Piece& operator=(Piece&& other) noexcept {
        if (this != &other) {
            sprite = std::move(other.sprite);
            texture = std::move(other.texture);
            active = other.active;
            type = std::move(other.type);
            color = other.color;
        }
        return *this;
    }

    // Lazy texture loading to save memory
    void loadTexture() {
        if (!texture) {
            texture = std::make_shared<sf::Texture>();
            if (!texture->loadFromFile("assets/pieces.bmp")) {
                std::cerr << "Error loading texture from file!" << std::endl;
                return;
            }
        }
        setTextureRect();
    }

    // Set the appropriate rectangle for the piece based on its type and color
    void setTextureRect() {
        // Define offsets for each piece type based on BMP layout
        constexpr int pieceWidth = 320;
        constexpr int pieceHeight = 320;

        int typeIndex = getPieceTypeIndex(type, color);
        if (typeIndex == -1) {
            std::cerr << "Invalid piece type or color!" << std::endl;
            return;
        }

        // Set texture rect and apply scaling
        sf::IntRect rect((typeIndex % 6) * pieceWidth, (typeIndex / 6) * pieceHeight, pieceWidth, pieceHeight);
        sprite.setTexture(*texture);
        sprite.setTextureRect(rect);

        // Scale down to 40x40 pixels
        sprite.setScale(40.0f / pieceWidth, 40.0f / pieceHeight);
    }

    // Get the piece type index from the type and color
    inline int getPieceTypeIndex(const std::string& pieceType, const sf::Color& pieceColor) const {
        if (pieceColor == sf::Color::White) {
            if (pieceType == "pawn") return 5;
            if (pieceType == "knight") return 3;
            if (pieceType == "bishop") return 2;
            if (pieceType == "rook") return 4;
            if (pieceType == "queen") return 1;
            if (pieceType == "king") return 0;
        } else { // Black pieces
            if (pieceType == "pawn") return 11;
            if (pieceType == "knight") return 9;
            if (pieceType == "bishop") return 8;
            if (pieceType == "rook") return 10;
            if (pieceType == "queen") return 7;
            if (pieceType == "king") return 6;
        }
        return -1; // Invalid piece type or color
    }

    // Draw the piece on the board
    inline void draw(sf::RenderWindow& window, float x, float y) {
        sprite.setPosition(x, y);
        window.draw(sprite);
    }

    // Check if the piece is active (on the board)
    inline bool isActive() const {
        return active;
    }

    // Set the piece as active or inactive
    inline void setActive(bool isActive) {
        active = isActive;
    }

    // Set the piece type and update its texture
    inline void setType(const std::string& pieceType) {
        type = pieceType;
        loadTexture();
    }

    // Set the piece color (white or black) and update texture
    inline void setColor(const sf::Color& pieceColor) {
        color = pieceColor;
        loadTexture();
    }

    // Get the piece type (e.g., "pawn", "knight")
    inline std::string getType() const {
        return type;
    }

    // Get the piece color (white or black)
    inline sf::Color getColor() const {
        return color;
    }
};

#endif // PIECE_H
