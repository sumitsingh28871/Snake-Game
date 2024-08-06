# Snake Game

## Overview

The Snake Game is a classic arcade game implemented in C++ where the player controls a snake that moves around the screen, eating fruits and avoiding walls. The game uses console-based graphics and input handling to provide a simple but engaging experience.

## Description

The game features a snake that moves around a defined area, eating fruits to grow longer. The game includes wall boundaries that the snake must avoid, and if the snake collides with itself or the wall, the game ends. The player's score increases each time the snake eats a fruit.

### Features

- **Snake Movement:** The snake moves in four directions (up, down, left, right).
- **Fruit Consumption:** The snake grows longer when it eats a fruit, and a new fruit appears in a random location.
- **Wall Boundaries:** The game area is bounded by walls, which the snake must avoid.
- **Score Tracking:** The game keeps track of the player's score based on the number of fruits eaten.
- **Menu and Help Screens:** Includes a menu for starting the game and a help screen for instructions.

## Requirements

- **Compiler:** A C++ compiler (e.g., g++, Visual Studio)
- **Operating System:** Windows (uses Windows-specific headers)

## Installation

1. **Clone the repository:**

    ```sh
    git clone https://github.com/yourusername/snake-game.git
    cd snake-game
    ```

2. **Compile the code:**

    For example, using `g++`:

    ```sh
    g++ -o snake_game main.cpp
    ```

    Replace `main.cpp` with the name of your source file if it's different.

3. **Run the executable:**

    ```sh
    ./snake_game
    ```

    On Windows, you may use:

    ```sh
    snake_game.exe
    ```

## Usage

1. **Start the Game:**

    After running the executable, you will see a menu screen. Press:
    - `z` to start the game.
    - `h` for help.
    - `q` to quit.

2. **Control the Snake:**

    Use the following keys to control the snake:
    - `w` to move up.
    - `s` to move down.
    - `a` to move left.
    - `d` to move right.
    - `m` to manually add a segment to the snake (useful for testing).

3. **End of Game:**

    The game ends if the snake collides with itself or the wall. The final score will be displayed.

## Code Overview

- `main.cpp`: Contains the main game logic and implementation of the `snake` class.
- `snake` class: Handles the movement, drawing, and collision detection of the snake.
- `drawWall()`: Draws the game boundaries.
- `draw()`: Draws the snake and fruit on the console.
- `move()`: Updates the snake's position based on user input.
- `collision()`: Detects collisions with walls or itself.

## Acknowledgments

- **Libraries and Tools:** This project uses standard C++ libraries and Windows-specific headers for console handling.

## Contact

For any questions or issues, please contact:

- **Your Name:** [Your Email]
- **GitHub:** [Your GitHub Profile]

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
