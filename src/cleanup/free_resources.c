/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:01:12 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/20 16:11:13 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void free_resources(t_game *game)
{
    int i;

    for (i = 0; i < 4; i++)
        mlx_destroy_image(game->mlx, game->textures[i].img);
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_image(game->mlx, game->img);
}
