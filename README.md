# A Simple 2D Skiing Game

A simple 2D skiing game created using C++ and the SDL3 library. Players control a skier descending a mountain, avoiding obstacles to score points. The objective is to survive as long as possible. Colliding with an obstacle results in a game over, displaying the player's score with an option to restart.

## Features:
- **Skiing Gameplay**: Navigate a skier down a mountain, avoiding obstacles while the speed increases over time.
- **Map**: Collision detection for the skier, utilizing a collision map (.bmp file). Different layers of decoration make up the background, random at each run.
- **ImGui Integration**: Debug tools accessible via `Ctrl+I`, allowing players to:
  - Set a custom high score
  - Adjust player speed with a slider
  - Control game speed with buttons
- **Menu System**: A simple menu to start the game.
- **Game Over Screen**: Displays the score and high score after a collision, with an option to restart.
- **High Score**: Tracks the highest score achieved during gameplay.
- **Obstacle Spawning**: Obstacles spawn every 2 seconds, reappearing at random positions on the X-axis once they go off-screen.
- **Background Music & Sound Effects**

## Game Controls:
- **Arrow Keys**: Move the skier left and right to avoid obstacles.
- **Enter**: Restart the game after death from the game over screen.

## Dependencies:
- SDL3
- SDL_image
- SDL_ttf
- ImGui

## Licenses:
- **MADE Mountain Font**
  - Type: Modern serif
  - License: Donationware
  - [Link](https://www.dafont.com/es/made-mountain.font)

- **Arcade Music Loop**
  - Type: 16-bit (8-bit style) loop
  - License: Free with credit (CC 4.0)
  - [Link](https://freesound.org/people/joshuaempyre/sounds/251461/)

  ## Images:
  ![Map1](https://i.imgur.com/RGPIwjy.png)
  ![DieScreen](https://i.imgur.com/1yW76E6.png)
  ![MainMenu](https://i.imgur.com/w36ace6.png)
  ![ImGui1](https://i.imgur.com/D526c35.png)