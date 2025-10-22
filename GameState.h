#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.h"

class GameState {
public:
    enum PlayStatus {
        WIN, LOSS, PLAYING
    }; // status of the game
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16),
              int _numberOfMines = 50); // constructs new game with specified dimensions & no of mines
    GameState(const char *filepath); // constructs new game from given filepath
    int getFlagCount(); // current number of flags
    int getMineCount(); // current number of mines on board
    Tile *getTile(int x, int y); // pointer of tile at coordinates
    PlayStatus getPlayStatus(); // get status of game
    void setPlayStatus(PlayStatus _status); // set game status
private:
    int numberOfMines = 0;
    int numberOfFlags;
    PlayStatus playStatus;
    sf::Vector2i dimensions;
    std::vector<Tile> tiles;

    void populateNeighbors(); // populate neighbors for each tile

    bool gameWon(); // check if game has been won
};