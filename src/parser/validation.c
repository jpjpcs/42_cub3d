/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:56:06 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/21 13:15:14 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int validate_config(t_game *game)
{
    if (game->config.res_x <= 0 || game->config.res_y <= 0)
        return (0);
    if (game->config.floor_color < 0 || game->config.ceiling_color < 0)
        return (0);
    if (game->config.floor_color > 0xFFFFFF || game->config.ceiling_color > 0xFFFFFF)
        return (0);
    if (game->config.no_texture == NULL || game->config.so_texture == NULL || game->config.we_texture == NULL || game->config.ea_texture == NULL || game->config.sprite_texture == NULL)
        return (0);
    return (1);
}

int validate_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map.map_height)
    {
        j = 0;
        while (j < game->map.map_width)
        {
            if (game->map.data[i][j] == 0)
            {
                if (i == 0 || i == game->map.map_height - 1 || j == 0 || j == game->map.map_width - 1)
                    return (0);
                if (game->map.data[i - 1][j] == 0 || game->map.data[i + 1][j] == 0 || game->map.data[i][j - 1] == 0 || game->map.data[i][j + 1] == 0)
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}
