#include <fstream>
#include <iostream>
#include <cstring>

#include "GameState.h"
#include "ToolBox.h"
#include "minesweeper.h"

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    dimensions = _dimensions;
    numberOfMines = _numberOfMines;

    std::vector<int> numberArray;
    // generate vector of 0s and 1s (0=normal, 1=bomb)
    for (int i = 0; i < numberOfMines; i++) {
        numberArray.push_back(1);
    }
    for (int i = 0; i < dimensions.x * dimensions.y - numberOfMines; i++) {
        numberArray.push_back(0);
    }
    // randomly shuffle vector
    std::random_shuffle(numberArray.begin(), numberArray.end());

    // map each vector item to a tile
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            if (numberArray[j + i * dimensions.x] == 0) {
                tiles.push_back(NormalTile(sf::Vector2f(j * 32, i * 32)));
            } else {
                tiles.push_back(BombTile(sf::Vector2f(j * 32, i * 32)));
            }
        }
    }

    // populate neighbors
    populateNeighbors();

    // set playStatus as PLAYING
    playStatus = PLAYING;
}

GameState::GameState(const char *filepath) {
    std::string line; // used to store content of lines in file
    int dimensionsX = 0; // x dimensions of board
    int dimensionsY = 0; // y dimensions of board
    std::ifstream file(filepath);

    while (std::getline(file, line)) {
        // check if line is empty / line contains characters other than 1 or 0
        if (!line.empty() && line[strspn(line.c_str(), "01")] == '\0') {
            // set x dimension to length of line
            dimensionsX = line.length();
            for (int i = 0; i < line.length(); i++) {
                // if 0 is read, store new normal tile
                // if 1 is read, store new bomb tile
                if (line[i] == '0') {
                    tiles.push_back(NormalTile(sf::Vector2f(i * 32, (dimensionsY) * 32)));
                } else if (line[i] == '1') {
                    tiles.push_back(BombTile(sf::Vector2f(i * 32, (dimensionsY) * 32)));
                    numberOfMines++;
                }
            }
            dimensionsY++; // increase dimensionsY by 1 for each line read
        } else { // if a line read is empty / contains unwanted characters, throw error
            std::cout << "ERROR: Input file invalid!";
            exit(1);
        }
    }

    // store dimensions
    dimensions = sf::Vector2i(dimensionsX, dimensionsY);

    // populate neighbors
    populateNeighbors();

    // set playStatus as PLAYING
    playStatus = PLAYING;
}

int GameState::getFlagCount() {
    numberOfFlags = 0;
    for (auto &tile: tiles) {
        if (tile.getState() == Tile::FLAGGED) {
            numberOfFlags++;
        }
    }
    return numberOfFlags;
}

int GameState::getMineCount() {
    return numberOfMines - getFlagCount();
}

Tile *GameState::getTile(int x, int y) {
    return &tiles[x + (y * dimensions.x)];
}

GameState::PlayStatus GameState::getPlayStatus() {
    if (gameWon()) // checks if gameWon returns true and sets playStatus to WIN
        setPlayStatus(WIN);
    return playStatus;
}

void GameState::setPlayStatus(PlayStatus _status) {
    playStatus = _status;

    if (getDebugMode() && playStatus == PLAYING) { // if debug mode turns on, reveal all mines
        for (auto &tile: tiles) {
            if (tile.getState() == Tile::HIDDEN) {
                tile.setState(Tile::EXPLODED);
            }
        }
    } else if (!getDebugMode() && playStatus == PLAYING) { // if debug mode gets turned off, hide mines
        for (auto &tile: tiles) {
            if (tile.getState() == Tile::EXPLODED) {
                tile.setState(Tile::HIDDEN);
            }
        }
    }
    if (playStatus == LOSS) { // if game lost, reveal all bomb tiles
        for (auto &tile: tiles) {
            if (tile.getState() == Tile::HIDDEN) {
                tile.setState(Tile::EXPLODED);
            }
        }
    }
}

// populate neighbors for each tile
void GameState::populateNeighbors() {
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            // top-left corner
            if (i == 0 && j == 0) {
                tiles[j + i * dimensions.x].setNeighbors({
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr,
                                                                 &tiles[1],
                                                                 nullptr,
                                                                 &tiles[dimensions.x],
                                                                 &tiles[dimensions.x + 1]
                                                         });
            }
                // top-right corner
            else if (i == 0 && j == dimensions.x - 1) {
                tiles[j + i * dimensions.x].setNeighbors({
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr,
                                                                 &tiles[j - 1],
                                                                 nullptr,
                                                                 &tiles[j - 1 + dimensions.x],
                                                                 &tiles[j + dimensions.x],
                                                                 nullptr
                                                         });
            }
                // bottom-left corner
            else if (i == dimensions.y - 1 && j == 0) {
                tiles[j + i * dimensions.x].setNeighbors({
                                                                 nullptr,
                                                                 &tiles[(i - 1) * dimensions.x],
                                                                 &tiles[(i - 1) * dimensions.x + 1],
                                                                 nullptr,
                                                                 &tiles[i * dimensions.x + 1],
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr
                                                         });
            }
                // bottom-right corner
            else if (i == dimensions.y - 1 && j == dimensions.x - 1) {
                tiles[j + i * dimensions.x].setNeighbors({
                                                                 &tiles[(i - 1) * dimensions.x + j - 1],
                                                                 &tiles[(i - 1) * dimensions.x + j],
                                                                 nullptr,
                                                                 &tiles[i * dimensions.x + j - 1],
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr
                                                         });
            }

                // left side
            else if (j == 0) {
                tiles[j + i * dimensions.x].setNeighbors({
                                                                 nullptr,
                                                                 &tiles[(i - 1) * dimensions.x],
                                                                 &tiles[(i - 1) * dimensions.x + 1],
                                                                 nullptr,
                                                                 &tiles[i * dimensions.x + 1],
                                                                 nullptr,
                                                                 &tiles[(i + 1) * dimensions.x],
                                                                 &tiles[(i + 1) * dimensions.x + 1]
                                                         });
            }
                // right side
            else if (j == dimensions.x - 1) {
                tiles[j + i * dimensions.x].setNeighbors({
                                                                 &tiles[(i - 1) * dimensions.x + j - 1],
                                                                 &tiles[(i - 1) * dimensions.x + j],
                                                                 nullptr,
                                                                 &tiles[i * dimensions.x + j - 1],
                                                                 nullptr,
                                                                 &tiles[(i + 1) * dimensions.x + j - 1],
                                                                 &tiles[(i + 1) * dimensions.x + j],
                                                                 nullptr
                                                         });
            }

                // top
            else if (i == 0) {
                tiles[j + i * dimensions.x].setNeighbors({
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr,
                                                                 &tiles[j - 1],
                                                                 &tiles[j + 1],
                                                                 &tiles[dimensions.x + j - 1],
                                                                 &tiles[dimensions.x + j],
                                                                 &tiles[dimensions.x + j + 1]
                                                         });
            }
                // bottom
            else if (i == dimensions.y - 1) {
                tiles[j + i * dimensions.x].setNeighbors({
                                                                 &tiles[(i - 1) * dimensions.x + j - 1],
                                                                 &tiles[(i - 1) * dimensions.x + j],
                                                                 &tiles[(i - 1) * dimensions.x + j + 1],
                                                                 &tiles[i * dimensions.x + j - 1],
                                                                 &tiles[i * dimensions.x + j + 1],
                                                                 nullptr,
                                                                 nullptr,
                                                                 nullptr
                                                         });
            }
                // other cases
            else {
                tiles[j + i * dimensions.x].setNeighbors({
                                                                 &tiles[(i - 1) * dimensions.x + j - 1],
                                                                 &tiles[(i - 1) * dimensions.x + j],
                                                                 &tiles[(i - 1) * dimensions.x + j + 1],
                                                                 &tiles[i * dimensions.x + j - 1],
                                                                 &tiles[i * dimensions.x + j + 1],
                                                                 &tiles[(i + 1) * dimensions.x + j - 1],
                                                                 &tiles[(i + 1) * dimensions.x + j],
                                                                 &tiles[(i + 1) * dimensions.x + j + 1]
                                                         });
            }
        }
    }
}

bool GameState::gameWon() {
    int revealedTiles = 0; // counts number of tiles that have been revealed in for-loop
    for (auto &tile: tiles) {
        if (tile.getState() == Tile::REVEALED) {
            revealedTiles++;
        }
    }
    if (revealedTiles == tiles.size() - numberOfMines) // if all non-mine tiles have been revealed
        return true;
    else
        return false;
}
