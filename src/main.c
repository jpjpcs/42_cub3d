/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:08:01 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/21 18:13:08 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int cleanup_game (t_game *game)
{
    int i;

    for (i = 0; i < 4; i++)
        mlx_destroy_image(game->mlx, game->textures[i].img);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_image(game->mlx, game->img);

    return (0);
}

int game_loop(t_game *game)
{
    if (game->keys.up)
        move_forward(game);
    if (game->keys.down)
        move_backward(game);
    /* if (game->keys.left)
        turn_left(game);
    if (game->keys.right)
        turn_right(game); */
    if (game->keys.left)
        strafe_left(game);
    if (game->keys.right)
        strafe_right(game);
   /*  if (game->keys.rotate_left)
        rotate_left(game);
    if (game->keys.rotate_right)
        rotate_right(game);
     */
    if (game->keys.esc)
        exit_game(game);
    draw(game);
    return (0);
}

void start_game_loop(t_game *game)
{
    //raycasting()
    mlx_hook(game->win, 2, 1L << 0, key_press, game);
    mlx_hook(game->win, 3, 1L << 1, key_release, game);
    mlx_hook(game->win, 17, 1L << 17, &cleanup_game, game);
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
}
// Instead of ft_bzero(game, sizeof(t_game)); // I could also use memset or calloc or just game = (t_game){0};
static void	init_game(t_game *game)
{
    ft_bzero(game, sizeof(t_game)); // I could also use memset or calloc or just game = (t_game){0};
    setup_game(game);
    setup_mlx(game);
    setup_textures(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_file(argc, argv[1]);
    check_map(argv[1]);
	init_game(&game);
	start_game_loop(&game);
	cleanup_game(&game);
	return (0);
}
/*
ou 


*/