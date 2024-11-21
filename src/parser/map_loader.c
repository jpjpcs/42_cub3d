/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:55:55 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/20 18:08:00 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void free_map(t_game *game)
{
    int i;

    i = 0;
    while (i < game->map.map_height)
    {
        free(game->map.data[i]);
        i++;
    }
    free(game->map.data);
}

int loadmap(t_game *game, const char *map_file)
{
    int fd;
    char *line;
    int i;
    int j;

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
        return (0);
    i = 0;
    while (get_next_line(fd) > 0)
    {
        j = 0;
        while (line[j])
        {
            if (line[j] == '1')
                game->map.data[i][j] = 1;
            else
                game->map.data[i][j] = 0;
            j++;
        }
        free(line);
        i++;
    }
    free(line);
    close(fd);
    return (1);
}
