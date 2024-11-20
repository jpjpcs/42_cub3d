/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:08:01 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/20 17:02:14 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	cleanup_game(t_game *game)
{
    int	i;

    i = 0;
    while (i < 4)
    {
        mlx_destroy_image(game->mlx, game->textures[i].img);
        i++;
    }
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_image(game->mlx, game->img);
}

int game_loop(t_game *game)
{
    if (game->keys.up)
        move_forward(game);
    if (game->keys.down)
        move_backward(game);
    if (game->keys.left)
        strafe_left(game);
    if (game->keys.right)
        strafe_right(game);
    if (game->keys.esc)
        exit_game(game);
    draw(game);
    return (0);
}

void start_game_loop(t_game *game)
{
    mlx_hook(game->win, 2, 1L << 0, key_press, game);
    mlx_hook(game->win, 3, 1L << 1, key_release, game);
    mlx_hook(game->win, 17, 1L << 17, exit_game, game);
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
}

static void	init_game(t_game *game, char *file)
{
    ft_bzero(game, sizeof(t_game));
    parse_config(game, file);
    setup_game(game);
    setup_mlx(game);
    setup_textures(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("Usage: ./cub3d <map.cub>"));
	init_game(&game, argv[1]);
	start_game_loop(&game);
	cleanup_game(&game);
	return (0);
}
/*
ou 


*/