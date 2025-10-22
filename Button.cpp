#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void()> _onClick) {
    position = _position;
    buttonClicked = _onClick;
}

sf::Vector2f Button::getPosition() {
    return position;
}

sf::Sprite *Button::getSprite() {
    return &sprite;
}

void Button::setSprite(sf::Sprite _sprite) {
    sprite = _sprite;
    sprite.setPosition(position);
}