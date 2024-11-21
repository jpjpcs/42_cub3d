/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:55:55 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/21 17:28:38 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
                game->map.grid[i][j] = 1;
            else
                game->map.grid[i][j] = 0;
            j++;
        }
        free(line);
        i++;
    }
    free(line);
    close(fd);
    return (1);
}
// mais copy_map ou load_map
/* static void	create_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		i;

	game->map.grid = ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!game->map.grid)
		exit_error(NULL, "Couldn't allocate memory.");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error(game, "Couldn't open requested file.");
	line = get_next_line(fd);
	i = -1;
	while (line)
	{
		game->map.grid[++i] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
} */
