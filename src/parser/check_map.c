/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcruz-an <rcruz-an@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:55:55 by joaosilva         #+#    #+#             */
/*   Updated: 2024/12/04 18:41:16 by rcruz-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_map_walls_floodfill(t_game *game, const int x, const int y)
{
	if (x < 0 || y < 0 || game->map.grid[y] == NULL
		|| x >= (int)ft_strlen(game->map.grid[y])
		|| game->map.grid[y][x] == ' ')
	{
		exit_error(game, "Map is not surrounded by walls.\n");
	}
	if (game->map.grid[y][x] == WALL)
		return ;
	game->map.grid[y][x] = '1';
	check_map_walls_floodfill(game, x + 1, y);
	check_map_walls_floodfill(game, x - 1, y);
	check_map_walls_floodfill(game, x, y + 1);
	check_map_walls_floodfill(game, x, y - 1);
}

void	set_spawn(t_game *game, int i, int j)
{
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (ft_strchr("NSEW", game->map.grid[i][j]))
			{
				if (game->player.x != 0 || game->player.y != 0)
					exit_error(game, "Multiple player spawn points found.\n");
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				game->player.dir_x = (game->map.grid[i][j] == 'E')
					- (game->map.grid[i][j] == 'W');
				game->player.dir_y = (game->map.grid[i][j] == 'S')
					- (game->map.grid[i][j] == 'N');
				game->player.plane_x = game->player.dir_x * FOV;
				game->player.plane_y = (game->player.dir_y * FOV) * -1;
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

/* void	check_empty_line_in_map(t_game *game)
{
	char	*map;
	int		last_line_len;
	int		found_digit;
	int		i;
	map = game->tmp_map_grid; // map is the map grid
	found_digit = 0; // Flag to track if we found any digit in a line
	while (*map)
	{
		last_line_len = ft_strclen(map, '\n'); // Get the length of the current line
		if (last_line_len > 0)
		{
			i = 0;
			while (i < last_line_len) // Loop through characters in the line
			{
				if (ft_isdigit(map[i]))
				{
					found_digit = 1; // A digit is found in this line
					break;
				}
				i++;
			}
		}
		else if (found_digit) // If a line is empty after finding digits
		{
			// If there's an empty line or invalid content after the map
			exit_error(game,
				"Invalid map: empty line found after the last map line with digits.\n");
		}
		map += last_line_len + 1; // Move to the next line
	}
} */

int	ft_line_has_map_chars(const char *str)
{
    while (*str && *str != '\n')
    {
        if (*str != '1' && *str != '0' && *str != 'W' && *str != ' ')
            return (0); // Caracteres inválidos encontrados
        str++;
    }
    return (1); // Todos os caracteres são válidos
}

int	ft_str_is_whitespace_or_empty(const char *str)
{
    while (*str)
    {
        if (*str != ' ' && *str != '\t' && *str != '\n')
            return (0); // Não é uma linha em branco
        str++;
    }
    return (1); // É uma linha em branco
}

void	check_trailing_lines(t_game *game)
{
	char	*map;
	int		is_inside_map;
	int		has_content_after_map;
	map = game->tmp_map_grid; // Ponteiro para o início do mapa
	is_inside_map = 1;        // Flag que indica se ainda estamos a processar o bloco do mapa
	has_content_after_map = 0;
	while (*map)
	{
		// Verifica se a linha atual contém apenas espaços ou está vazia
		if (ft_str_is_whitespace_or_empty(map))
		{
			if (!is_inside_map) // Se já saímos do mapa, as linhas vazias são válidas
				has_content_after_map = 1;
		}
		else if (is_inside_map) // Linha não vazia ou com caracteres do mapa
		{
			if (ft_line_has_map_chars(map)) // Verifica se a linha contém apenas caracteres do mapa (1, 0, W)
				is_inside_map = 1;
			else
				exit_error(game, "Invalid map: unexpected characters in map block.\n");
		}
		else // Conteúdo após linhas vazias (invalida o mapa)
		{
			exit_error(game, "Invalid map: extra content found after map block.\n");
		}
		// Avança para a próxima linha
		map += ft_strclen(map, '\n') + 1;
	}
	// Se não encontrou conteúdo após o mapa, a validação é concluída com sucesso
	if (has_content_after_map)
		return;
}

void print_map(t_game *game)
{
    int i;

    i = 0;
    while (game->map.grid[i])
    {
        printf("%s\n", game->map.grid[i]);
        i++;
    }
}

void	parse_check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	check_map_characters(game);
	check_trailing_lines(game);
	game->map.grid = ft_split(game->tmp_map_grid, '\n');
	if (!game->map.grid)
		exit_error(game, "Memory allocation failed in ft_split.\n");
	set_spawn(game, i, j);
	check_map_walls_floodfill(game, game->player.x, game->player.y);
	ft_free_array(game->map.grid);
	game->map.grid = ft_split(game->tmp_map_grid, '\n');
	if (!game->map.grid)
		exit_error(game, "Memory allocation failed in ft_split.\n");
	print_map(game);
}
