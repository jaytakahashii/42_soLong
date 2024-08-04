<h1 align="center">
	SOLONG(Projects at 42tokyo)
</h1>

<p align="center">
	<img src="./img/Screenshot 2024-08-04 171105.png" width="700">
</p>

<p align="center">
	<b><i>Final Score 100/100</i></b><br>
</p>

# 💡 About the project

> This project is a very small 2D game.
> Its purpose is to make you work with textures, sprites, and some other very basic gameplay elements.
> (Reference: 42Tokyo solong project PDF)

## Overview
Solong is a project from the 42 curriculum that involves creating a simple 2D game.
The objective is to gain a deeper understanding of game development concepts such as textures, sprites, and basic gameplay mechanics.
This project provides an opportunity to explore various aspects of game design and implementation using the minilibx library.

## Key Features
- **2D Game Development**: The project involves creating a small 2D game with basic gameplay elements.
- **Texture and Sprite Management**: Learn to work with textures and sprites to create visually appealing game elements.
- **Basic Gameplay Mechanics**: Implement basic gameplay features such as movement, collision detection, and event handling.
- **Minilibx Library**: Utilize the minilibx library for graphics rendering and handling window events.

## Objectives
- **Understanding Game Development**: Gain insights into the fundamentals of game development, including graphics rendering and gameplay mechanics.
- **System Programming**: Enhance skills in system-level programming using C, focusing on game-related concepts.
- **Graphics Handling**: Learn to manage and manipulate textures and sprites for creating game visuals.
- **Event Handling**: Implement event handling for player input and game interactions.

# 🚀 Algorithm
The solong project involves creating a basic 2D game where the player can move around a map, interact with objects, and reach a goal. Here is a simplified explanation of the algorithm:

1. **Initialize Game**:
   - Load textures and sprites using the minilibx library.
   - Set up the game window and event handlers.

2. **Game Loop**:
   - Continuously check for player input and update the game state accordingly.
   - Handle player movement and collision detection with the environment.
   - Render the updated game state on the screen.

3. **Player Interaction**:
   - Allow the player to interact with objects in the game world.
   - Implement basic gameplay mechanics such as collecting items and reaching the goal.

# 🛠️ Usage

### Requirements

- The library is written in C language and needs the **`cc` compiler**.
- the minilibx library

### Instructions

**1. Compiling the code**

To compile the  libft library and this project code, go to its path and run:

```shell
$ make
```

**2. Run**
After creating the executable file `so_long`, you provide the numbers you want to sort as command line arguments.

```shell
./so_long <map_file>
```
**Controls**
- **Movement**: Use `W`, `A`, `S`, and `D` keys, or the arrow keys to move the player character around the map.
- **Objectiv**: Navigate through the map, interact with objects, and reach the designated goal to complete the level.

**+α. Cleaning all binary (.o) and executable files**

To clean all files generated while doing a make, go to the path and run:

```shell
$ make fclean
```
