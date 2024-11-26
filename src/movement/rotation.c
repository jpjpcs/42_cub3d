/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:58:59 by joaosilva         #+#    #+#             */
/*   Updated: 2024/11/20 15:59:00 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Rotation matrix */

// [ cos(a) - sin(a) ]
// [ sin(a) + cos(a) ]

void rotate_left(t_game *game)
{
    double	sin_;
	double	cos_;
	double	old_dir_x;
	double	old_plane_x;

	sin_ = sin(game->player.rot_speed);
	cos_ = cos(game->player.rot_speed);

	old_dir_x = game->player.dir_x;                                             //Antigo dir_x para calcular o dir_y
	game->player.dir_x = game->player.dir_x * cos_ - game->player.dir_y * sin_; //Aplicar a formula
	game->player.dir_y = old_dir_x * sin_ + game->player.dir_y * cos_;

	old_plane_x = game->player.plane_x;                                         //Mesma coisa com os planes
	game->player.plane_x = game->player.plane_x * \
		cos_ - game->player.plane_y * sin_;
	game->player.plane_y = old_plane_x * sin_ + game->player.plane_y * cos_;
}

/* Igual ao de cima */
void rotate_right(t_game *game)
{
    double	sin_;
	double	cos_;
	double	old_dir_x;
	double	old_plane_x;

	sin_ = sin(-game->player.rot_speed); // negative
	cos_ = cos(-game->player.rot_speed);

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_ - game->player.dir_y * sin_;
	game->player.dir_y = old_dir_x * sin_ + game->player.dir_y * cos_;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * \
		cos_ - game->player.plane_y * sin_;
	game->player.plane_y = old_plane_x * sin_ + game->player.plane_y * cos_;
}