#include <iostream>
#include "Tile.h"
#include "ToolBox.h"

Tile::Tile(sf::Vector2f _position) {
    position = _position;
    setState(HIDDEN);
}

sf::Vector2f Tile::getLocation() {
    return position;
}

Tile::State Tile::getState() {
    return state;
};

std::array<Tile *, 8> &Tile::getNeighbors() {
    return neighbors;
}

void Tile::setState(State _state) {
    state = _state;
    switch (state) {
        case REVEALED:
            // handle number textures & sprites
            if (neighborMines != 0) {
                switch (neighborMines) {
                    case 1:
                        numberTexture.loadFromFile("images/number_1.png");
                        break;
                    case 2:
                        numberTexture.loadFromFile("images/number_2.png");
                        break;
                    case 3:
                        numberTexture.loadFromFile("images/number_3.png");
                        break;
                    case 4:
                        numberTexture.loadFromFile("images/number_4.png");
                        break;
                    case 5:
                        numberTexture.loadFromFile("images/number_5.png");
                        break;
                    case 6:
                        numberTexture.loadFromFile("images/number_6.png");
                        break;
                    case 7:
                        numberTexture.loadFromFile("images/number_7.png");
                        break;
                    case 8:
                        numberTexture.loadFromFile("images/number_8.png");
                        break;
                }
                numberSprite.setTexture(numberTexture);
                numberSprite.setPosition(position);
            }
            ToolBox::getInstance()->gameState->getPlayStatus(); // checks if game has been won (a.k.a. if last normal tile has been revealed)
            break;
        case EXPLODED:
            if (ToolBox::getInstance()->gameState->getPlayStatus() == GameState::PLAYING &&
                !ToolBox::getInstance()->debugMode) {
                ToolBox::getInstance()->gameState->setPlayStatus(GameState::LOSS); // if mine is clicked, game is lost
            }
            break;
    }
}

void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {
    neighbors = _neighbors;
    // count no of neighbor mines
    for (Tile *item: neighbors) {
        if (item != nullptr) {
            if (item->type == 1) {
                neighborMines++;
            }
        }
    }
}

void Tile::onClickLeft() {
    if (state != FLAGGED) {
        revealNeighbors();
    }
}

void Tile::onClickRight() {
    if (state == HIDDEN) { // if tile hidden, flag on right click
        setState(FLAGGED);
    } else if (state == FLAGGED) { // if tile flagged, remove flag
        setState(HIDDEN);
    }
}

void Tile::draw() {
    sf::RenderWindow *window = &ToolBox::getInstance()->window;
    switch (state) { // draw different sprites depending on state
        case HIDDEN:
            hiddenTileTexture.loadFromFile("images/tile_hidden.png");
            hiddenTileSprite.setTexture(hiddenTileTexture);
            hiddenTileSprite.setPosition(position);
            window->draw(hiddenTileSprite);
            break;
        case REVEALED:
            revealedTileTexture.loadFromFile("images/tile_revealed.png");
            revealedTileSprite.setTexture(revealedTileTexture);
            revealedTileSprite.setPosition(position);
            window->draw(revealedTileSprite); // draw revealed sprite on bottom
            window->draw(numberSprite); // draw number sprite on top
            break;
        case EXPLODED:
            // no need to load hiddenTile texture from file, since it will be already loaded
            hiddenTileSprite.setPosition(position);
            window->draw(hiddenTileSprite); // draw hidden sprite on bottom
            // if tile is mine, draw mine sprite on top; if tile is not mine, only display hiddenTile sprite
            if (type == 1) {
                explodedTileTexture.loadFromFile("images/mine.png");
                explodedTileSprite.setTexture(explodedTileTexture);
                explodedTileSprite.setPosition(position);
                window->draw(explodedTileSprite);
            }
            break;
        case FLAGGED:
            // no need to load hiddenTile texture from file, since it will be already loaded
            hiddenTileSprite.setPosition(position);
            flaggedTileTexture.loadFromFile("images/flag.png");
            flaggedTileSprite.setTexture(flaggedTileTexture);
            flaggedTileSprite.setPosition(position);
            window->draw(hiddenTileSprite);
            window->draw(flaggedTileSprite);
            break;
    }
}

void Tile::revealNeighbors() {
    // if normal tile and not flagged, reveal tile (and neighbors if there's 0 mine neighbors)
    if (type == 0) {
        if (state != FLAGGED)
            setState(REVEALED);
        if (neighborMines == 0) {
            for (Tile *item: neighbors) {
                if (item != nullptr && item->state != REVEALED) {
                    item->revealNeighbors();
                }
            }
        }
    } else { // if mine, explode
        setState(EXPLODED);
    }
}