/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcruz-an <rcruz-an@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:59:19 by joaosilva         #+#    #+#             */
/*   Updated: 2024/12/03 10:27:26 by rcruz-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int get_pixil(t_texture *texture, int x, int y)
{
    return (*(unsigned int *)(texture->addr + \
		(y * texture->len) + (x * (texture->bits_per_pixel / 8))));
}

static int put_pixil(t_game *game, int x, int y, int color)
{
    char *dest;

    dest = game->pixels.addr + (y * game->pixels.len + x * 
        (game->pixels.bits_per_pixel / 8));
    *(unsigned int *)dest = color;
}

/* Upper half will be the ceiling COLOR, the bottom half will be the floor COLOR*/
static void draw_background(t_game *game)
{
    int x;
    int y;

    x = -1;
    y = -1;
    while (++y < SCREEN_HEIGHT)
    {
        while (++x < SCREEN_WIDTH)
        {
            if (y > SCREEN_HEIGHT / 2)
                put_pixil(&game, x, y, game->floor_color); //check with the updated .h
            else
                put_pixil(&game, x, y, game->ceiling_color); //check with the updated .h
        }
        x = -1;
    }
}

int darken_color(int color, double perp_wall_dist)
{
 	int	r;
	int	g;
	int	b;

	perp_wall_dist /= 5;
	if (perp_wall_dist < 1)
		return (color);
	r = (color >> 16) / perp_wall_dist;
	g = (color >> 8 & 0xFF) / perp_wall_dist;
	b = (color & 0xFF) / perp_wall_dist;
	return (r << 16 | g << 8 | b);   
}

void init_draw(t_game *game)
{
    /* Add this part to the "init" folder maybe? */
    int i;

    i = -1;
    while (++i < 4) 
	{
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img, 
			&game->textures[i].bits_per_pixel, &game->textures[i].len,
			&game->textures[i].endian);
		if (!game->textures[i].addr)
			exit_error(game, "Failed to get texture address");
	}

    /* Init draw */
	game->pixels.width = (int)SCREEN_WIDTH;
	game->pixels.height = (int)SCREEN_HEIGHT;
	game->pixels.img = mlx_new_image(game->mlx, game->pixels.width,
			game->pixels.height);
	if (!game->pixels.img)
		exit_error(game, "Failed to create new image");
	game->pixels.addr = mlx_get_data_addr(game->pixels.img,
			&game->pixels.bits_per_pixel, &game->pixels.len, &game->pixels.endian);
	if (!game->pixels.addr)
		exit_error(game, "Failed to get image address");
	/* game->win = mlx_new_window(game->mlx, game->pixels.width,
			game->pixels.height, "Cub3D_"); */

}

void draw(t_game *game, int x)
{
    int		y;
	int		tex_y;
	int		color;

	y = -1;
	while (y < game->draw.end)
	{
		tex_y = (int)game->draw.pos & (TEXTURE_HEIGHT - 1);
		game->draw.pos += game->draw.step;
		color = get_pixil(&game->textures[game->ray.reached_wall], game->ray.hit, tex_y);
		color = darken_color(color, game->ray.perp_wall_dist);
		put_pixil(&game->pixels, x, y, color);
		y++;
	}
}
