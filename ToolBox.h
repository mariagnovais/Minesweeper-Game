#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "GameState.h"

class ToolBox {
    ToolBox();

    sf::Texture debugButtonTexture;
    sf::Sprite debugButtonSprite;
    sf::Texture newGameButtonTexture;
    sf::Sprite newGameButtonSprite;
    sf::Texture test1ButtonTexture;
    sf::Sprite test1ButtonSprite;
    sf::Texture test2ButtonTexture;
    sf::Sprite test2ButtonSprite;
public:
    ~ToolBox(); // destructor

    sf::RenderWindow window; // SFML app window
    GameState *gameState; // primary game state representation
    Button *debugButton; // reveals mines in debug mode
    Button *newGameButton; // resets / starts new game
    Button *testButton1; // loads test board 1
    Button *testButton2; // loads test board 2

    bool debugMode = false;

    static ToolBox *getInstance(); // returns instance of toolbox

    // win/lose textures
    sf::Texture winTexture;
    sf::Sprite winSprite;
    sf::Texture lossTexture;
    sf::Sprite lossSprite;

    // digits textures
    sf::Texture digitsTexture;
    std::vector<sf::Sprite> digitsSpriteArray;
};