# Tic Tac Toe Game

A modern implementation of the classic Tic Tac Toe game built with SDL2 in C++. Features both human vs human and human vs computer gameplay modes with an undefeatable AI opponent.

## Features

- **Two Game Modes:**
  - Human vs Human: Play against a friend locally
  - Human vs Computer: Challenge an undefeatable AI opponent
- **Graphical Interface**: Clean, intuitive GUI built with SDL2
- **Smart AI**: Computer opponent uses strategic algorithms to ensure it never loses
- **Easy Navigation**: Simple menu system with restart and main menu options
- **Cross-Platform**: Compatible with Windows, Linux, and macOS

## Screenshots

*Game showcases a clean interface with clear X and O symbols, intuitive button controls, and smooth gameplay.*

## Prerequisites

Before building and running the game, ensure you have:

- **C++ Compiler** (GCC, Clang, or MSVC)
- **SDL2 Development Libraries**
- **SDL2_ttf Development Libraries**
- **CMake** (optional, for easier building)

### Installing Dependencies

#### Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-ttf-dev build-essential
```

#### macOS (using Homebrew):
```bash
brew install sdl2 sdl2_ttf
```

#### Windows:
Download SDL2 and SDL2_ttf development libraries from:
- [SDL2 Download](https://www.libsdl.org/download-2.0.php)
- [SDL2_ttf Download](https://www.libsdl.org/projects/SDL_ttf/)

## Project Structure

```
tic-tac-toe/
├── main.cpp                    # Main game file
├── All_Functions.c             # Game logic and AI functions
├── GameFiles/
│   ├── includeSDL/SDL2/        # SDL2 headers
│   ├── includeTTF/SDL2/        # SDL2_ttf headers
│   └── fonts/                  # Game fonts
│       ├── Bageta400.ttf       # Heading font
│       └── Babyboggie400.ttf   # Button font
└── README.md
```

## Building the Game

### Method 1: Direct Compilation

```bash
# Clone the repository
git clone https://github.com/DeviceDidWhat/TickTacToe_Game.git
cd tic-tac-toe

# Compile the game
g++ -o tic_tac_toe main.cpp -lSDL2 -lSDL2_ttf -lm

# Run the game
./tic_tac_toe
```

### Method 2: Using Makefile (if available)

```bash
make
./tic_tac_toe
```

## How to Play

1. **Launch the Game**: Run the executable to open the main menu
2. **Choose Game Mode**: 
   - Click "Play with Player" for human vs human mode
   - Click "Play with Computer" to challenge the AI
3. **Make Your Move**: Click on any empty cell to place your symbol
4. **Game Controls**:
   - **Restart**: Start a new game with the same mode
   - **Main Menu**: Return to the main menu to change game modes

## Game Rules

- Players take turns placing X's and O's on a 3×3 grid
- The first player to get three symbols in a row (horizontally, vertically, or diagonally) wins
- If all cells are filled without a winner, the game ends in a draw
- In human vs computer mode, the player is always X and goes first

## AI Algorithm

The computer opponent implements a sophisticated strategy that makes it **undefeatable**:

- **Strategic Opening**: Prioritizes center and corner positions
- **Winning Moves**: Always takes a winning move when available
- **Blocking**: Prevents the player from winning by blocking potential winning moves
- **Pattern Recognition**: Recognizes and responds to common player strategies
- **Optimal Play**: Uses game theory principles to ensure optimal moves

The AI is designed to either win or draw - it will never lose a game when playing optimally.

## Controls

- **Mouse**: Click to interact with buttons and make moves
- **Left Click**: Select cells, buttons, and menu options
- **Window Close**: Exit the game

## Technical Details

- **Language**: C++
- **Graphics Library**: SDL2
- **Text Rendering**: SDL2_ttf
- **Resolution**: 600x700 pixels
- **Grid Size**: 3×3 with 200px cells

## Customization

You can easily customize the game by modifying:

- **Colors**: Change RGB values in the rendering functions
- **Fonts**: Replace font files in the `GameFiles/fonts/` directory
- **Window Size**: Modify `SCREEN_WIDTH` and `SCREEN_HEIGHT` constants
- **AI Difficulty**: Adjust the AI logic in `All_Functions.c`

## Troubleshooting

### Common Issues:

1. **SDL2 not found**: Ensure SDL2 development libraries are properly installed
2. **Font loading errors**: Verify font files exist in the correct directory
3. **Compilation errors**: Check that all required headers are included
4. **Missing functions**: Ensure `All_Functions.c` is properly linked

### Debug Mode:
The game outputs winner information to the console for debugging purposes.

## Contributing

Contributions are welcome! Please feel free to submit issues, fork the repository, and create pull requests.

### Areas for Improvement:
- Sound effects and background music
- Animated transitions
- Score tracking across multiple games
- Network multiplayer support
- Mobile touch controls


## Author

Created with passion for classic games and modern programming techniques.

## Acknowledgments

- SDL2 community for excellent documentation
- Font creators for the beautiful typefaces
- Classic game developers who inspired this implementation

---

**Enjoy playing Tic Tac Toe! Challenge yourself against the undefeatable AI or play with friends!**
