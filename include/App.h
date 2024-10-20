#include <SFML/Graphics.hpp> // Include necessary headers
#include <vector>
#include <memory> // For std::unique_ptr
#include "RenderObject.h"
#include "Objects/chessboard.h"
#include "Objects/UI.h"
#include "Audio/DJ.h"
class App {
private:
    sf::RenderWindow window;                     // Window object for rendering
    Chessboard chessboard;                       // Direct Chessboard object (avoid dynamic allocation)
    UI ui;                                       // Direct UI object (avoid dynamic allocation)
    DJ dj; // DJ instance for managing audio
    std::vector<RenderObject*> renderObjects;    // Pointers to renderable objects to avoid unique_ptr overhead

public:
    // Constructor
    App() 
        : window(sf::VideoMode(800, 600), "Chess Game"), 
          chessboard(window),                    // Initialize chessboard with window reference
          ui(window)                             // Initialize UI with window reference
    {
        setUp();                                 // Setup pieces and objects
    }

    // Setup pieces on the chessboard
    void placePieces() {
        static const std::array<const char*, 8> initialRowPieces = {"rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"};

        // Place white pieces
        for (int col = 0; col < 8; ++col) {
            chessboard.setPiece(0, col, std::make_unique<Piece>(initialRowPieces[col], sf::Color::White));
            chessboard.setPiece(1, col, std::make_unique<Piece>("pawn", sf::Color::White)); // Pawns
        }

        // Place black pieces
        for (int col = 0; col < 8; ++col) {
            chessboard.setPiece(7, col, std::make_unique<Piece>(initialRowPieces[col], sf::Color::Black));
            chessboard.setPiece(6, col, std::make_unique<Piece>("pawn", sf::Color::Black)); // Pawns
        }
    }

    // Setup all objects
    void setUp() {
        placePieces();
        initializeAudio(); // Load audio files
        // Add direct pointers to renderable objects
        renderObjects.push_back(&ui);
        renderObjects.push_back(&chessboard);
    }

    void initializeAudio() {
        dj.loadBackgroundMusic("bg_music", "assets/DJConrad/NintendoType1.ogg");
        //dj.loadSoundEffect("move_piece", "path/to/move_sound.ogg");
        dj.playBackgroundMusic("bg_music"); // Start background music
    }
    // Update all renderable objects
    void updateAll() {
        for (auto* object : renderObjects) {
            object->update();  // Call update on each object
        }
    }

    // Render all renderable objects
    void renderAll() {
        for (auto* object : renderObjects) {
            object->render();  // Call render on each object
        }
    }

    // Event handling and main loop
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    ui.handleMouseClick(mousePosition);  // Handle left-click in UI
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    int col = event.mouseButton.x / chessboard.getSquareSize();  // Use square size from chessboard
                    int row = event.mouseButton.y / chessboard.getSquareSize();
                    //Piece* piece = chessboard.getPieceAt(row, col);  // Fetch piece
                    //ui.handleRightClick(row, col, piece);           // Handle right-click
                }
            }
        }
    }

    // Run the main application loop
    void run() {
        while (window.isOpen()) {
            handleEvents();        // Handle events separately
            window.clear(sf::Color::Magenta);
            updateAll();           // Update game objects
            renderAll();           // Render game objects
            window.display();      // Display the result
        }
    }
};
