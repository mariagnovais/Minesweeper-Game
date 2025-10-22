#pragma once

#include "minesweeper.h"

void debugButtonFunc() {
    std::cout << "debug mode toggled\n";
    toggleDebugMode();
}

void newGameButtonFunc() {
    restart();
}

void test1ButtonFunc() {
    if (getDebugMode()) // turn off debug mode
        toggleDebugMode();
    delete ToolBox::getInstance()->gameState;
    ToolBox::getInstance()->gameState = new GameState("boards/testboard1.brd");
}

void test2ButtonFunc() {
    if (getDebugMode()) // turn off debug mode
        toggleDebugMode();
    delete ToolBox::getInstance()->gameState;
    ToolBox::getInstance()->gameState = new GameState("boards/testboard2.brd");
}
