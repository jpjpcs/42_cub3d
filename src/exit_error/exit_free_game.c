/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:01:22 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/21 17:14:39 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* void free_resources(t_game *game)
{
    int i;

    for (i = 0; i < 4; i++)
        mlx_destroy_image(game->mlx, game->textures[i].img);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_image(game->mlx, game->img);
} */


static void	free_textures(t_game *game)
{
    int i;

    i = -1;
    while(++i <= 4)
		if (game->img[i].img)
        	mlx_destroy_image(game->mlx, game->texture[i].img);
	/* if (game->img_walls.img)
		mlx_destroy_image(game->mlx, game->img_walls.img);
	if (game->img_space.img)
		mlx_destroy_image(game->mlx, game->img_space.img);
	if (game->img_exit.img)
		mlx_destroy_image(game->mlx, game->img_exit.img);
	if (game->img_collect.img)
		mlx_destroy_image(game->mlx, game->img_collect.img);
	if (game->img_player.img)
		mlx_destroy_image(game->mlx, game->img_player.img); */
}

void free_map(t_game *game)
{
    int i;

    i = 0;
    while (i < game->map.map_height)
    {
        free(game->map.grid[i]);
        i++;
    }
    free(game->map.grid);
}

static void	free_game(t_game *game)
{
	if (game)
	{
		if (game->map.grid)
			free_map(game->map.grid);
		free_textures(game);
		if (game->mlx && game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	}
}

int	exit_esc(t_game *game)
{
	ft_putendl_fd("You gave up! See you soon!", 1);
	free_game(game);
	exit(EXIT_SUCCESS);
}

int	exit_game(t_game *game, char *msg)
{
	ft_putendl_fd(msg, 1);
	free_game(game);
	exit(EXIT_SUCCESS);
}

int	exit_error(t_game *game, char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	free_game(game);
	exit(EXIT_FAILURE);
}
