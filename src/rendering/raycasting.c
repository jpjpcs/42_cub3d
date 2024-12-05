/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcruz-an <rcruz-an@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:59:28 by joaosilva         #+#    #+#             */
/*   Updated: 2024/12/04 16:57:55 by rcruz-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* fabs() --> absolute value */
/* delta_dist.y = fabs(1/ray_dir.y) */
static void init_dda(t_game *game)
{
    game->ray.reached_wall = -1; //For DDA
    game->ray.delta_dist_x = 1e30 * (game->ray.dir_x == 0) // If ray_dir is 0 (parallel to x-axis), set the distance to a high value number to avoid division by 0
        + fabs(1.0 / (game->ray.dir_x + (game->ray.dir_x == 0))); //Formula --> delta_dist.x = fabs(1/ray_dir.x)
    game->ray.delta_dist_y = 1e30 * (game->ray.dir_y == 0)
        + fabs(1.0 / (game->ray.dir_y + (game->ray.dir_y == 0)));
    game->ray.side_dist_x = fabs((game->player.x - game->map.checker.x)        //Exact position on the grid cell
                    - (game->ray.dir_x > 0)) * game->ray.delta_dist_x; // (ray_dir.x > 0) based whether the next grid cell is in the positive or negative direction
                                                                       // *delta to convert map units into screen_width
    game->ray.side_dist_y = fabs((game->player.y - game->map.checker.y)
                    - (game->ray.dir_y > 0)) * game->ray.delta_dist_y;
}

static void init_raycast(t_game *game, int x)
{
    game->ray.camera_x = 2 * x / (float)game->pixels.width -1; //[-1, 1] // -1 is the leftmost side of the screen
    game->ray.dir_x = game->player.dir_x + game->player.plane_x * game->ray.camera_x; //Ray direction in x (left to right based on camera_x value)
    game->ray.dir_y = game->player.dir_y + game->player.plane_y * game->ray.camera_x; //Ray direction in y
    game->ray.step_x = (game->ray.dir_x < 0) * -2 + 1; // -1 or 1 (left or right)
    game->ray.step_y = (game->ray.dir_y < 0) * -2 + 1; // -1 or 1 (down or up)
    game->map.checker.x = (int)(game->player.x); //Player's position as an INT to identify the grid cell (map block)
    game->map.checker.y = (int)(game->player.y);
}

/* Raycasting loop */
int raycast(t_game *game)
{
    int horizontal_pixels;
    
    game->pixels.width = SCREEN_WIDTH; // Temp
    horizontal_pixels = 0;
    handle_keys(game);
    while (game->pixels.width > horizontal_pixels++)
    {
        printf("------------------------------------\n");
        init_raycast(game, horizontal_pixels);
        init_dda(game);
        dda_calculations(game);
        draw(game, horizontal_pixels);
    }
    mlx_put_image_to_window(game->mlx, game->win, game->pixels.img, 0, 0); // NOT SURE ABOUT THIS ONE
    return 0;
}