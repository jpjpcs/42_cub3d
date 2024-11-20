/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:45:17 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/20 16:04:01 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
//# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

// ------------ Macros ------------
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

// ------------ Structs ------------

// Map struct
typedef struct s_map 
{
    char **data; // Map data: 2D array of characters. Each character represents a different element of the map.
    int map_width;
    int map_height;
} t_map;

// Keys struct
typedef struct s_keys 
{
    int up;
    int down;
    int left;
    int right;
    int esc;
} t_keys;

// Texture struct
typedef struct s_texture 
{
    void *img; // Image of the texture itself.
    //char *addr;
    int width;
    int height;
} t_texture;

// Player struct
typedef struct s_player 
{
    double pos_x; // Player´s X position
    double pos_y; // Player´s Y position
    double dir_x; // Player´s direction vector X
    double dir_y; // Player´s direction vector Y
    double plane_x; // Player´s camera plane X
    double plane_y; // Player´s camera plane Y
    float move_speed; // Player´s movement speed
    float rot_speed; // Player´s rotation speed
} t_player;

// Main game struct
typedef struct s_game 
{
    // MLX variables (graphic library)
    void *mlx; // Instance of the mlx library. To allow interaction with the graphic system.
    void *win; // Game window to be rendered. The window where the game will be displayed.
    void *img; // Image to be rendered. The image that will be displayed on the window and that´s the background of the game.

    // Game Map (2D representation)
    t_map map; // The Map of the game: map structure. Contains the map data and its dimensions (width and height).
    
    // Players properties
    t_player player; // Player´s information: position, direction, etc
    
    // Game controls
    t_keys keys; // Keys controls: up, down, left, right arrows and ESC. 
    
    // Textures
    t_texture textures[4]; // Texture for the 4 directions for walls and sprites: north, south, east, west.
    
    // Screen size
    int screen_width; // Screen/Window width and height.
    int screen_height;
} t_game;

// ------------ Prototypes ------------
void init_game(t_game *game);
void render_game(t_game *game);
void handle_keys(t_game *game);
void move_player(t_game *game);
void load_textures(t_game *game);

// ------------ Error Handling ------------
int error_exit(const char *msg);

#endif

/*
cub3d/
├── include/
│   ├── cub3d.h
│   ├── parser.h
│   ├── game.h
│   ├── movement.h
│   ├── rendering.h
│   └── cleanup.h
├── src/
│   ├── main.c
│   ├── parser/
│   │   ├── config.c
│   │   ├── map_loader.c
│   │   └── validation.c
│   ├── init/
│   │   ├── setup_game.c
│   │   ├── setup_mlx.c
│   │   └── setup_textures.c
│   ├── movement/
│   │   ├── player_input.c
│   │   ├── movement_utils.c
│   │   └── rotation.c
│   ├── rendering/
│   │   ├── draw.c
│   │   ├── raycasting.c
│   │   └── textures.c
│   ├── cleanup/
│   │   ├── free_resources.c
│   │   └── exit_game.c


cub3d/
├── include/
│   ├── cub3d.h
├── src/
│   ├── main.c
│   ├── parser/
│   │   ├── config.c
│   │   ├── map_loader.c
│   │   └── validation.c
│   ├── init/
│   │   ├── setup_game.c
│   │   ├── setup_mlx.c
│   │   └── setup_textures.c
│   ├── movement/
│   │   ├── player_input.c
│   │   ├── movement_utils.c
│   │   └── rotation.c
│   ├── rendering/
│   │   ├── draw.c
│   │   ├── raycasting.c
│   │   └── textures.c
│   ├── cleanup/
│   │   ├── free_resources.c
│   │   └── exit_game.c
*/
