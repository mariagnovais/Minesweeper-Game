#include "ToolBox.h"
#include "ButtonFunc.h"

ToolBox::ToolBox() : window(sf::VideoMode(800, 600), "P4 - Minesweeper, Matis Luzi") {

    // new game button
    newGameButtonTexture.loadFromFile("images/face_happy.png");
    newGameButtonSprite.setTexture(newGameButtonTexture);
    sf::Vector2f newGameButtonPosition(368, 524);
    newGameButton = new Button(newGameButtonPosition, newGameButtonFunc);
    newGameButton->setSprite(newGameButtonSprite);

    // debug button
    debugButtonTexture.loadFromFile("images/debug.png");
    debugButtonSprite.setTexture(debugButtonTexture);
    sf::Vector2f debugButtonPosition(496, 524);
    debugButton = new Button(debugButtonPosition, debugButtonFunc);
    debugButton->setSprite(debugButtonSprite);

    // test button 1
    test1ButtonTexture.loadFromFile("images/test_1.png");
    test1ButtonSprite.setTexture(test1ButtonTexture);
    sf::Vector2f test1ButtonPosition(560, 524);
    testButton1 = new Button(test1ButtonPosition, test1ButtonFunc);
    testButton1->setSprite(test1ButtonSprite);

    // test button 2
    test2ButtonTexture.loadFromFile("images/test_2.png");
    test2ButtonSprite.setTexture(test2ButtonTexture);
    sf::Vector2f test2ButtonPosition(624, 524);
    testButton2 = new Button(test2ButtonPosition, test2ButtonFunc);
    testButton2->setSprite(test2ButtonSprite);

    // smiley face (WIN)
    winTexture.loadFromFile("images/face_win.png");
    winSprite.setTexture(winTexture);
    winSprite.setPosition(368, 524);

    // sad face (LOSS)
    lossTexture.loadFromFile("images/face_lose.png");
    lossSprite.setTexture(lossTexture);
    lossSprite.setPosition(368, 524);

    // digits
    digitsTexture.loadFromFile("images/digits.png");
    for (int i = 0; i < 11; i++) {
        digitsSpriteArray.push_back(sf::Sprite(digitsTexture));
        digitsSpriteArray[i].setTextureRect(sf::IntRect(sf::Vector2i(i * 21, 0), sf::Vector2i(21, 32)));
    }

    // gameState
    gameState = new GameState();
}

ToolBox *ToolBox::getInstance() { // returns/creates instance of ToolBox
    static ToolBox toolBoxInstance;
    return &toolBoxInstance;
}

// destructor
ToolBox::~ToolBox() {
    delete gameState;
    delete newGameButton;
    delete debugButton;
    delete testButton1;
    delete testButton2;
}
