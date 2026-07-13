*This project has been created as part of the 42 curriculum by rhoogend, fgreiff.*

# Cub3D

## Description

Cub3D is a small first-person 3D renderer written in C with MiniLibX. The project is inspired by early raycasting games such as Wolfenstein 3D: a 2D map is parsed from a `.cub` configuration file, the player is placed inside the map, and rays are cast from the player viewpoint to render textured walls in a pseudo-3D perspective.

The goal of the project is to build a complete graphical program that combines file parsing, map validation, player movement, collision checks, raycasting mathematics, texture loading, and real-time rendering through MiniLibX.

## Features

- Parses a `.cub` map description file.
- Loads four XPM wall textures: north, south, west, and east.
- Reads and validates floor and ceiling RGB definitions from the map file.
- Validates that the map contains only valid characters and is closed by walls.
- Requires exactly one player spawn position: `N`, `S`, `E`, or `W`.
- Initializes player direction and camera plane from the spawn orientation.
- Uses raycasting to render a first-person wall view.
- Applies basic fish-eye correction when calculating projected wall height.
- Selects wall textures according to the wall side that was hit by the ray.
- Supports keyboard movement and rotation.
- Displays a small 2D minimap overlay with visible cast rays.
- Frees allocated memory and destroys MiniLibX resources on exit.

## Instructions

### Requirements

This project is written in C and uses MiniLibX. On a Linux/X11 setup, the following system libraries are usually needed:

```bash
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev
```

MiniLibX must also be available in the location expected by the project `Makefile`.

### Compilation

From the root of the repository, compile the project with:

```bash
make
```

Useful Makefile rules:

```bash
make        # build the executable
make clean  # remove object files
make fclean # remove object files and executable
make re     # rebuild from scratch
```

### Execution

Run the program with one `.cub` map file as the only argument:

```bash
./cub3D maps/example.cub
```

The program expects exactly one argument. If the file cannot be opened, the map is invalid, a texture cannot be loaded, or an RGB value is malformed, the program exits with an error message.

## Controls

| Key | Action |
| --- | --- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| Left arrow | Rotate left |
| Right arrow | Rotate right |
| `ESC` | Exit the program |
| Window close button | Exit the program |

## Map File Format

A valid `.cub` file contains six configuration lines followed by the map layout.

Example:

```text
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm
F 220,100,0
C 225,30,0

111111111
100000001
100N00001
100000001
111111111
```

### Texture identifiers

| Identifier | Meaning |
| --- | --- |
| `NO` | Path to the north wall texture |
| `SO` | Path to the south wall texture |
| `WE` | Path to the west wall texture |
| `EA` | Path to the east wall texture |

### Color identifiers

| Identifier | Meaning | Format |
| --- | --- | --- |
| `F` | Floor color | `R,G,B` |
| `C` | Ceiling color | `R,G,B` |

RGB values must contain exactly three integer values in the range `0` to `255`.

### Map characters

| Character | Meaning |
| --- | --- |
| `1` | Wall |
| `0` | Empty walkable space |
| `N` | Player spawn, facing north |
| `S` | Player spawn, facing south |
| `E` | Player spawn, facing east |
| `W` | Player spawn, facing west |
| Space | Void/outside of the map |

The map must be closed: every walkable tile and the player spawn must be surrounded by valid map cells and cannot touch the outside void. The map must contain one, and only one, player spawn.

## Technical Overview

### Program flow

1. Allocate and initialize the main `t_game` structure.
2. Read the `.cub` file and extract texture paths, RGB values, and map data.
3. Validate texture/color definitions and map structure.
4. Initialize the player position, direction vector, and camera plane.
5. Initialize raycasting parameters, including field of view and projection plane distance.
6. Create the MiniLibX window and images.
7. Load XPM textures into MiniLibX image buffers.
8. Enter the render loop.

### Raycasting

The renderer casts rays across a 60-degree field of view. For each ray, the engine checks vertical and horizontal grid intersections, compares their distances, and keeps the closest wall hit. The distance is corrected using the ray angle relative to the player direction to reduce fish-eye distortion. The corrected distance is then used to calculate the height of the wall slice drawn on screen.

### Movement and collision

Movement is based on the player direction vector and camera plane:

- Forward/backward movement uses the direction vector.
- Strafing uses the camera plane vector.
- Rotation updates both the direction vector and the camera plane.

Before updating the player position, the target cell is checked against the map. Movement into a wall tile is blocked.

### Textures

The program loads four XPM textures with MiniLibX. During rendering, it chooses the texture according to whether the ray hit a vertical or horizontal wall and according to the ray direction. The texture X coordinate is calculated from the fractional part of the wall hit position.

### Minimap

A minimap is rendered into a smaller MiniLibX image and displayed on top of the main render. It shows map tiles and projected ray lines, which makes debugging player position and ray hits easier.

## Project Structure

The implementation is organized around these responsibilities:

```text
main.c                    Program entry point and initialization flow
Cub3d.h                   Main structs, constants, and function prototypes
map_extract*.c            Map file reading and configuration extraction
validate_map.c            Map closure and player-count validation
validate_rgb.c            RGB syntax and range validation
init_player.c             Player spawn, direction, and camera plane setup
init_rays.c               Field of view and raycasting setup
raycasting.c              Ray-wall hit selection
hor_inter.c               Horizontal grid intersection checks
vert_inter.c              Vertical grid intersection checks
draw_game.c               3D wall rendering and texture sampling
draw_mm.c                 Minimap rendering
movements.c               MiniLibX hooks and key state handling
player_movement.c         Movement and collision checks
rotate_player.c           Direction/camera plane rotation
init_textures.c           XPM texture loading and cleanup
init_window.c             MiniLibX window/image setup
clean_up.c                Memory and MiniLibX cleanup
e_handling.c              Error handling
```

## Resources

- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Lode Vandevenne: Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Permadi: Raycasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [42 Docs: MiniLibX Images](https://harm-smits.github.io/42docs/libs/minilibx/images.html)
- [Xlib Events documentation](https://tronche.com/gui/x/xlib/events/)
- `math.h` documentation for trigonometric functions such as `sin`, `cos`, `tan`, `sqrt`, `floor`, and `ceil`.

### AI usage

AI assistance was used for documentation support: summarizing the existing project structure, drafting this README, and improving the wording of the setup, usage, map-format, and technical-overview sections. 
AI assistance was partially used to support understanding while debugging.

