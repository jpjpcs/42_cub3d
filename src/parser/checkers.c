/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:42:01 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/22 13:00:42 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* void check_map(char *file_name)
{
    int fd;
    char *line;
    int ret;

    line = NULL;
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
		exit_error(NULL, "Couldn't open requested file.");
    line = get_next_line(fd);
    
    if (fd < 0)
        exit_error(NULL, "Couldn´t open requested file. Please insert a corrected file.");
    while ((ret = get_next_line(fd)) > 0)
    {
        if (line[0] == '1' || line[0] == '0')
            break;
        free(line);
    }
    if (ret <= 0)
        exit_error(NULL, "Error\nInvalid map\n");
    free(line);
    close(fd);
} */
/* int parse_line(t_game *game, char *line)
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
} */

/* static void	check_characters(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.rows)
	{
		j = -1;
		while (++j < game->map.cols)
		{
			if (game->map.grid[i][j] == PLAYER)
			{
				game->player_count++;
				game->player.current = (t_point){j, i};
				game->player.next = (t_point){j, i};
			}
			else if (game->map.grid[i][j] == EXIT)
				game->exit++;
			else if (game->map.grid[i][j] == COLLECT)
				game->collect++;
			else if (!ft_strchr(TILLES, game->map.grid[i][j]))
				exit_error(game, "Invalid character in map.");
		}
	}
	if (game->player_count != 1 || game->exit != 1 || game->collect < 1)
		exit_error(game, "Wrong number of players, exits or collectibles.");
} */

/* static void	check_textures(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map.rows)
		if (game->map.grid[i][0] != WALL || game->map.grid[i][game->map.cols
			- 1] != WALL)
			exit_error(game, "Map is not surrounded by walls.");
	i = -1;
	while (++i < game->map.cols)
		if (game->map.grid[0][i] != WALL || game->map.grid[game->map.rows
			- 1][i] != WALL)
			exit_error(game, "Map is not surrounded by walls.");
} */

int	check_walls_floodfill(t_game *game, char **map, const int x, const int y)
{
	if (x < 0 || y < 0 || y >= game->map.height
		|| x >= (int)ft_strlen(map[y]) || map[y][x] == 32)
	{
		printf("Invalid Map(Not Wall Closed)\n");
		free_double_pointer_array(map);
		ft_quit_game(game);
	}
	if (map[y][x] == '1')
		return (1);
	map[y][x] = '1';
	check_walls_floodfill(game, map, x + 1, y);
	check_walls_floodfill(game, map, x - 1, y);
	check_walls_floodfill(game, map, x, y + 1);
	check_walls_floodfill(game, map, x, y - 1);
	return (0);
}

void check_map(char *file_name)
{
    char	**grid;
    int valid_map;
	int		i;

    i = 0;
    grid = ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!grid)
		exit_error(game, "Couldn't allocate memory.");
    i = -1;
	while (++i < game->map.rows)
	{
		grid[i] = ft_strdup(game->map.grid[i]);
		if (!grid[i])
		{
			//free_map(grid);
			exit_error(game, "Couldn't allocate memory.");
		}
	}
    valid_map = check_walls_floodfill (game, grid, game->player.y, game->player.x);
    if (!valid_map)
		exit_error(game, "Map has invalid path.");
    check_textures (file_name); //check color is inside 0-255 RGB.
    check_characters (file_name);
    free_map(grid);
}

// Verifies if number of args are correct. Verifies if name of the file, extension are correct and if file opens.
void check_file(int argc, char *file_name)
{
    int len;
    int fd;
    
    len = ft_strlen(file_name);
    if (argc != 2)
        exit_error(NULL, "Error\nInvalid number of arguments\n");
    if (len < 5)
        exit_error(NULL,"Error\nInvalid file name\n");
    if (ft_strncmp(file_name + len - 4, ".cub", 4) != 0)
        exit_error(NULL, "Error\nInvalid file extension\n");
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        exit_error(NULL,
			"Couldn´t open requested file. Please insert a corrected file.");
    close(fd);
}
