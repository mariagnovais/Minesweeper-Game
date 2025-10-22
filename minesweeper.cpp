#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "ToolBox.h"
#include "minesweeper.h"

int launch() {

    ToolBox *toolBox = ToolBox::getInstance();
    sf::RenderWindow *window = &ToolBox::getInstance()->window;

    while (window->isOpen()) {
        // Process events
        sf::Event event;
        eventHandler(&event, window);

        // Clear screen
        window->clear();

        // Render everything
        render();

        // Update the window
        window->display();
    }

    return 0;
}

void restart() {
    if (getDebugMode())
        toggleDebugMode();
    delete ToolBox::getInstance()->gameState;
    ToolBox::getInstance()->gameState = new GameState();
}

void render() {
    sf::RenderWindow *window = &ToolBox::getInstance()->window;

    // Draw buttons
    window->draw(*ToolBox::getInstance()->debugButton->getSprite()); // debug button
    window->draw(*ToolBox::getInstance()->newGameButton->getSprite()); // new game button
    window->draw(*ToolBox::getInstance()->testButton1->getSprite()); // test 1 button
    window->draw(*ToolBox::getInstance()->testButton2->getSprite()); // test 2 button

    // Draw digits for mine counter
    std::array<char, 3> mineDigits = getDigits(ToolBox::getInstance()->gameState->getMineCount());
    for (int i = 0; i < 3; i++) {
        switch (mineDigits[i]) {
            case '0':
                ToolBox::getInstance()->digitsSpriteArray[0].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[0]);
                break;
            case '1':
                ToolBox::getInstance()->digitsSpriteArray[1].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[1]);
                break;
            case '2':
                ToolBox::getInstance()->digitsSpriteArray[2].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[2]);
                break;
            case '3':
                ToolBox::getInstance()->digitsSpriteArray[3].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[3]);
                break;
            case '4':
                ToolBox::getInstance()->digitsSpriteArray[4].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[4]);
                break;
            case '5':
                ToolBox::getInstance()->digitsSpriteArray[5].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[5]);
                break;
            case '6':
                ToolBox::getInstance()->digitsSpriteArray[6].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[6]);
                break;
            case '7':
                ToolBox::getInstance()->digitsSpriteArray[7].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[7]);
                break;
            case '8':
                ToolBox::getInstance()->digitsSpriteArray[8].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[8]);
                break;
            case '9':
                ToolBox::getInstance()->digitsSpriteArray[9].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[9]);
                break;
            case '-':
                ToolBox::getInstance()->digitsSpriteArray[10].setPosition(i * 21 + 28, 540);
                window->draw(ToolBox::getInstance()->digitsSpriteArray[10]);
                break;
        }
    }

    // Draw tiles
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            ToolBox::getInstance()->gameState->getTile(j, i)->draw();
        }
    }

    // Draw win/loss sprite
    if (ToolBox::getInstance()->gameState->getPlayStatus() == GameState::WIN) {
        window->draw(ToolBox::getInstance()->winSprite);
    } else if (ToolBox::getInstance()->gameState->getPlayStatus() == GameState::LOSS) {
        window->draw(ToolBox::getInstance()->lossSprite);
    }

}

void eventHandler(sf::Event *event, sf::RenderWindow *window) {
    while (window->pollEvent(*event)) {
        // Close window: exit
        if (event->type == sf::Event::Closed) {
            window->close();
        }

        // left mouse clicked on debug button
        if (event->type == sf::Event::MouseButtonPressed
            && event->mouseButton.button == sf::Mouse::Left
            && ToolBox::getInstance()->debugButton->getSprite()->getGlobalBounds().contains(
                window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
            ToolBox::getInstance()->debugButton->onClick();
            break;
        }

        // left mouse clicked on new game button
        if (event->type == sf::Event::MouseButtonPressed
            && event->mouseButton.button == sf::Mouse::Left
            && ToolBox::getInstance()->newGameButton->getSprite()->getGlobalBounds().contains(
                window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
            ToolBox::getInstance()->newGameButton->onClick();
            break;
        }

        // left mouse clicked on test 1 button
        if (event->type == sf::Event::MouseButtonPressed
            && event->mouseButton.button == sf::Mouse::Left
            && ToolBox::getInstance()->testButton1->getSprite()->getGlobalBounds().contains(
                window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
            ToolBox::getInstance()->testButton1->onClick();
            break;
        }

        // left mouse clicked on test 2 button
        if (event->type == sf::Event::MouseButtonPressed
            && event->mouseButton.button == sf::Mouse::Left
            && ToolBox::getInstance()->testButton2->getSprite()->getGlobalBounds().contains(
                window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
            ToolBox::getInstance()->testButton2->onClick();
            break;
        }

        // left click on tile
        if (ToolBox::getInstance()->gameState->getPlayStatus() ==
            GameState::PLAYING) { // check if gameState==PLAYING (when not, tiles do not respond to clicks)
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 25; j++) {
                    if (event->type == sf::Event::MouseButtonPressed
                        && event->mouseButton.button == sf::Mouse::Left
                        && window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x >= j * 32
                        && window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x < j * 32 + 32
                        && window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y >= i * 32
                        && window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y < i * 32 + 32
                            ) {
                        ToolBox::getInstance()->gameState->getTile(j, i)->onClickLeft();
                        break;
                    }
                }
            }

            // right click on tile
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 25; j++) {
                    if (event->type == sf::Event::MouseButtonPressed
                        && event->mouseButton.button == sf::Mouse::Right
                        && window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x >= j * 32
                        && window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x < j * 32 + 32
                        && window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y >= i * 32
                        && window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y < i * 32 + 32
                            ) {
                        ToolBox::getInstance()->gameState->getTile(j, i)->onClickRight();
                        break;
                    }
                }
            }
        }
    }
}

void toggleDebugMode() {
    if (ToolBox::getInstance()->debugMode)
        ToolBox::getInstance()->debugMode = false;
    else
        ToolBox::getInstance()->debugMode = true;
    ToolBox::getInstance()->gameState->setPlayStatus(
            GameState::PLAYING); // needed so that GameState can tell that game isn't over when mines are revealed
}

bool getDebugMode() {
    return ToolBox::getInstance()->debugMode;
}

std::array<char, 3> getDigits(int number) {
    std::array<char, 3> digits;

    // if 3 digit positive / 2 digit negative
    if ((number > 99 && number < 1000) || (number > -100 && number < -9)) {
        // if negative number with 2 digits, 1st char of array is '-'
        // otherwise, n-th char is taken from int-to-string
        digits[0] = std::to_string(number)[0];
        digits[1] = std::to_string(number)[1];
        digits[2] = std::to_string(number)[2];
    }
        // if 2 digit positive / 1 digit negative
    else if ((number > 9) || (number > -10 && number < 0)) {
        (number > -10 && number < 0) ? digits[0] = '-' : digits[0] = '0';
        (number > -10 && number < 0) ? digits[1] = '0' : digits[1] = std::to_string(number)[0];
        digits[2] = std::to_string(number)[1];
    }
        // if 1 digit positive
    else if (number >= 0) {
        digits[0] = '0';
        digits[1] = '0';
        digits[2] = std::to_string(number)[0];
    } else {
        std::cout << "ERROR: Mine counter value invalid!";
        exit(1);
    }
    return digits;
}

int main() {
    return launch();
}
