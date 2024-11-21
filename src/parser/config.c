/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:55:32 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/20 18:15:55 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int parse_line(t_game *game, char *line)
{
    if (line[0] == 'R')
        return (parse_resolution(game, line));
    else if (line[0] == 'F')
        return (parse_floor_color(game, line));
    else if (line[0] == 'C')
        return (parse_ceiling_color(game, line));
    else if (line[0] == 'N' && line[1] == 'O')
        return (parse_texture(game, line, 0));
    else if (line[0] == 'S' && line[1] == 'O')
        return (parse_texture(game, line, 1));
    else if (line[0] == 'W' && line[1] == 'E')
        return (parse_texture(game, line, 2));
    else if (line[0] == 'E' && line[1] == 'A')
        return (parse_texture(game, line, 3));
    else if (line[0] == 'S')
        return (parse_texture(game, line, 4));
    else if (line[0] == '1' || line[0] == '0')
        return (parse_map(game, line));
    return (1);
}

int load_config(t_game *game, const char *config_file)
{
    int fd;
    char *line;

    fd = open(config_file, O_RDONLY);
    if (fd < 0)
        return (0);
    while (get_next_line(fd) > 0)
    {
        if (!parse_line(game, line))
        {
            free(line);
            close(fd);
            return (0);
        }
        free(line);
    }
    free(line);
    close(fd);
    return (1);
}

int load_config(t_game *game, const char *config_file)
{
    int fd;
    char *line;

    fd = open(config_file, O_RDONLY);
    if (fd < 0)
        return (0);
    while (get_next_line(fd, &line) > 0)
    {
        if (!parse_line(game, line))
        {
            free(line);
            close(fd);
            return (0);
        }
        free(line);
    }
    free(line);
    close(fd);
    return (1);
}

