/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcruz-an <rcruz-an@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:55:55 by joaosilva         #+#    #+#             */
/*   Updated: 2024/12/03 20:08:18 by rcruz-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_map_walls_floodfill(t_game *game, const int x, const int y)
{
	if (x < 0 || y < 0 || game->map.grid[y] == NULL
		|| x >= (int)ft_strlen(game->map.grid[y])
		|| game->map.grid[y][x] == ' ')
	{
		printf("Str: %s\n", game->map.grid[y]);
		printf("X: %d\n", x);
		printf("Y: %d\n", y);
		exit_error(game, "Map is not surrounded by walls.\n");
	}
	if (game->map.grid[y][x] == WALL)
		return ;
	/* printf("Char: %c\n", game->map.grid[y][x]); */
	game->map.grid[y][x] = '1';
	check_map_walls_floodfill(game, x + 1, y);
	check_map_walls_floodfill(game, x - 1, y);
	check_map_walls_floodfill(game, x, y + 1);
	check_map_walls_floodfill(game, x, y - 1);
}

void	set_spawn(t_game *game, int i, int j)
{
	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (ft_strchr("NSEW", game->map.grid[i][j]))
			{
				if (game->player.x != 0 || game->player.y != 0)
					exit_error(game, "Multiple player spawn points found.\n");
				game->player.x = j;
				game->player.y = i;
				game->player.dir_x = (game->map.grid[i][j] == 'E')
					- (game->map.grid[i][j] == 'W');
				game->player.dir_y = (game->map.grid[i][j] == 'S')
					- (game->map.grid[i][j] == 'N');
				game->map.grid[i][j] = FLOOR;
			}
			j++;
		}
		i++;
	}
	if (game->player.x == 0 || game->player.y == 0)
		exit_error(game, "Valid player spawn point not found.\n");
}

int	check_map_characters(t_game *game)
{
	char	*line;

	line = game->tmp_map_grid;
	while (*line)
	{
		if (!ft_strchr(" 01NSWE\n", *line))
		{
			printf("Invalid map character: %c\n", *line);
			exit_error(game, "Invalid map character.\n");
			return (1);
		}
		line++;
	}
	return (0);
}

/* void	print_map(t_game *game)
{
	int		i;
	char	*map;
	int		last_line_len;

	i = 0;
	while (game->map.grid[i])
	{
		printf("%s\n", game->map.grid[i]);
		i++;
	}
} */
void	check_empty_line_in_map(t_game *game)
{
	char	*map;
	int		last_line_len;

	map = game->tmp_map_grid;
	last_line_len = ft_strclen(map, '\n');
	map += last_line_len + 1;
	while (*map)
	{
		if (!last_line_len && ft_strclen(map, '\n'))
			exit_error(game,
				"Invalid map: number found after map and empty line.\n");
		last_line_len = ft_strclen(map, '\n');
		map += last_line_len + 1;
	}
}

void	parse_check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_map_characters(game);
	/* printf("Map grid: %s\n", game->tmp_map_grid); */
	check_empty_line_in_map(game);
	game->map.grid = ft_split(game->tmp_map_grid, '\n');
	if (!game->map.grid)
		exit_error(game, "Memory allocation failed in ft_split.\n");
	set_spawn(game, i, j);
	/* printf("Player spawn point: %f, %f\n", game->player.x, game->player.y); */
	check_map_walls_floodfill(game, game->player.x, game->player.y);
	ft_free_array(game->map.grid);
	game->map.grid = ft_split(game->tmp_map_grid, '\n');
	if (!game->map.grid)
		exit_error(game, "Memory allocation failed in ft_split.\n");
	//print_map(game);
}
