#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include "Piece.h"  // Include your Piece class header
#include "RenderObject.h"  // Include the RenderObject class header

class Chessboard : public RenderObject {
private:
    sf::RenderWindow& window;                       // Reference to the render window (no extra allocation)
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;  // 8x8 fixed array for pieces
    const int squareSize;                           // Size of each square on the chessboard (constant)
    const sf::Color lightColor;                     // Color for light squares (constant)
    const sf::Color darkColor;                      // Color for dark squares (constant)

public:
    // Constructor
    Chessboard(sf::RenderWindow& win, int squareSize = 50,
               sf::Color lightColor = sf::Color(222, 184, 135),  // Light color
               sf::Color darkColor = sf::Color(139, 69, 19))     // Dark color
        : window(win), squareSize(squareSize), lightColor(lightColor), darkColor(darkColor) {
        // Initialize the chessboard with nullptr (no pieces)
        for (auto& row : board) {
            for (auto& cell : row) {
                cell = nullptr;
            }
        }
    }

    // Inherited update method (add any necessary logic)
    void update() override {
        // Implement logic if necessary to update chessboard state
    }

    // Inherited render method
    void render() override {
        // Draw the chessboard squares
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
                square.setPosition(col * squareSize, row * squareSize);
                square.setFillColor((row + col) % 2 == 0 ? lightColor : darkColor);
                window.draw(square); // Draw the square
            }
        }

        // Draw pieces on the chessboard
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (board[row][col] && board[row][col]->isActive()) {  // Check if there's an active piece
                    board[row][col]->draw(window, col * squareSize, row * squareSize);
                }
            }
        }
    }

    // Get square size
    int getSquareSize() const {
        return squareSize;
    }

    // Place a piece on the chessboard
    void setPiece(int row, int col, std::unique_ptr<Piece> piece) {
        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
            board[row][col] = std::move(piece);  // Use smart pointer to manage piece memory
        }
    }

    // Get a piece at a specific position
    Piece* getPiece(int row, int col) const {
        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
            return board[row][col].get();  // Return raw pointer for access, no ownership
        }
        return nullptr;
    }
};

#endif // CHESSBOARD_H
