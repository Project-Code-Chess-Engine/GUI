#include <memory>
#include <SFML/Graphics.hpp>
#include "Display.h"

class App {
private:
    std::shared_ptr<sf::RenderWindow> window;
    std::unique_ptr<Display> display;
public:
    App();
    void run();
};