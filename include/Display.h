#include <board.h>
#include <SFML/Graphics.hpp>
#include <memory>

class Display {
private:
    std::weak_ptr<sf::RenderTarget> sufrace;
public:
    Display(std::weak_ptr<sf::RenderTarget> surface);
    void drawPiece(int row, int col, Piece piece);
    void drawDot(int row, int col);
    void drawCircle(int row, int col);
    void drawBackground();
    void drawLayer(uint64_t board, Piece piece);
    void clear();
};