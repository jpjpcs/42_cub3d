/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:08:01 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/20 14:36:08 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


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