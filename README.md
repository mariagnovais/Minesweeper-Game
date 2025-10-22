# Minesweeper Game

A desktop implementation of the classic Minesweeper puzzle written in modern C++ and rendered with [SFML](https://www.sfml-dev.org/). The project recreates the traditional 25 × 16 board with responsive controls, animated sprites, and several helper buttons for debugging and deterministic test layouts.

## Features

- **Classic gameplay** – Left click to reveal tiles and right click to place flags while the mine counter keeps track of remaining bombs.
- **Debug mode** – Temporarily reveal all bombs without ending the game for easier troubleshooting of the logic.
- **Preset board loaders** – Quickly swap to the `boards/testboard1.brd` and `boards/testboard2.brd` layouts via the toolbar buttons.
- **Smiley face status** – The new-game button doubles as the familiar smiley indicator that changes when you win or lose.
- **Modular codebase** – Core concepts such as tiles, buttons, and game state are implemented as reusable C++ classes.

## Project structure

```
Minesweeper-Game/
├── Button.cpp/.h           # UI button sprite and click handling
├── ButtonFunc.h            # Callbacks for toolbar buttons
├── GameState.cpp/.h        # Board generation, win/loss checks, and tile management
├── Tile.cpp/.h             # Tile hierarchy (normal vs. bomb, drawing logic)
├── ToolBox.cpp/.h          # Singleton resource manager (window, textures, sprites)
├── window.h                # Window constants
└── minesweeper.cpp/.h      # Main loop, rendering, event dispatch
```

The runtime also expects the following asset folders next to the executable:

- `images/` – Sprites for tiles, digits, and toolbar buttons (`face_happy.png`, `face_win.png`, `face_lose.png`, `debug.png`, `test_1.png`, `test_2.png`, `digits.png`, tile textures, etc.).
- `boards/` – Text-based board layouts used by the test buttons (e.g., `testboard1.brd`, `testboard2.brd`). Each file uses `0` for empty tiles and `1` for mines.

## Prerequisites

- A C++17-compatible compiler (GCC, Clang, or MSVC).
- [SFML 2.5](https://www.sfml-dev.org/download.php) or newer (graphics module required).
- Asset pack placed in the `images/` directory and optional board files in `boards/`.

On Debian/Ubuntu you can install SFML with:

```bash
sudo apt-get install libsfml-dev
```

## Building

1. Clone the repository and enter the project folder.
2. Ensure SFML headers and libraries are discoverable by your compiler.
3. Compile the sources, linking against the SFML graphics, window, and system libraries. For example with GCC:

```bash
g++ -std=c++17 -I. \
    Button.cpp GameState.cpp Tile.cpp ToolBox.cpp minesweeper.cpp \
    -o minesweeper \
    -lsfml-graphics -lsfml-window -lsfml-system
```

4. Place the `images/` and `boards/` directories alongside the generated `minesweeper` executable.

## Running the game

Launch the compiled binary:

```bash
./minesweeper
```

### Controls

- **Left click** on a tile to reveal it.
- **Right click** on a tile to toggle a flag.
- **Smiley button** resets the board with a fresh random layout.
- **Debug button** toggles the global debug mode (reveals or hides all bombs while keeping the game alive).
- **Test 1 / Test 2 buttons** load the deterministic layouts from `boards/testboard1.brd` and `boards/testboard2.brd`.

The mine counter at the bottom-left updates based on the number of remaining mines minus placed flags. Winning reveals the happy face; triggering a mine displays the sad face and reveals the full board.

## Customizing boards

To create your own layouts, add additional `.brd` files to the `boards/` directory using rows of `0` and `1`. You can then modify `ButtonFunc.h` or extend the UI to hook your new boards into the test buttons.
