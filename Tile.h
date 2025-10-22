#pragma once

#include <SFML/Graphics.hpp>

class Tile {
public:
    enum State {
        REVEALED, HIDDEN, FLAGGED, EXPLODED
    }; // current state of tile
    Tile(sf::Vector2f _position);

    sf::Vector2f getLocation(); // get position of tile
    State getState(); // get state of tile
    std::array<Tile *, 8> &getNeighbors(); // get array of neighboring tiles
    void setState(State _state); // set state of tile
    void setNeighbors(std::array<Tile *, 8> _neighbors); // populate/replace neighbors with given array
    void onClickLeft(); // behavior when tile left-clicked
    void onClickRight(); // behavior when tile right-clicked
    void draw(); // render tile to the screen according to its state
protected:
    void revealNeighbors(); // set state to revealed, based on state & content of neighbors
    int type = 0; // type of tile: 0 if normal tile, 1 if mine
private:
    State state;
    sf::Vector2f position;
    std::array<Tile *, 8> neighbors;

    // type of tile (0 of normal tile, 1 if mine)
    int neighborMines = 0; // number of neighbors that are mines

    // sprites and textures
    sf::Texture hiddenTileTexture;
    sf::Sprite hiddenTileSprite;
    sf::Texture revealedTileTexture;
    sf::Sprite revealedTileSprite;
    sf::Texture flaggedTileTexture;
    sf::Sprite flaggedTileSprite;
    sf::Texture explodedTileTexture;
    sf::Sprite explodedTileSprite;
    // numbers
    sf::Texture numberTexture;
    sf::Sprite numberSprite;
};

class NormalTile : public Tile {
public:
    NormalTile(sf::Vector2f _position) : Tile(_position) {
        type = 0;
    };
};

class BombTile : public Tile {
public:
    BombTile(sf::Vector2f _position) : Tile(_position) {
        type = 1;
    };
};