#pragma once

int launch(); // starts app

void restart(); // starts new random game

void render(); // renders UI elements

void eventHandler(sf::Event *event, sf::RenderWindow *window); // handles events such as mouse clicks

void toggleDebugMode(); // toggles debug mode

bool getDebugMode(); // returns the value of debug mode

std::array<char, 3> getDigits(int number); // splits number into 3 individual digits, used for mine counter