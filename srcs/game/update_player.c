/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:06:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/15 14:36:40 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* if no changes have been made, return 0, otherwise 1 */

static int	is_data_updated(t_player *ply, double prev_x,
	double prev_y, double prev_ang)
{
	if (ply->pos_x == prev_x && ply->pos_y == prev_y && ply->ang_y == prev_ang)
		return (0);
	return (1);
}

/* If this is out of the map, we put the player back to his previous position */

static void	correct_pos(t_game *game, t_player *ply,
	double prev_pos_x, double prev_pos_y)
{
	if (game->infomap->map[(int)ply->pos_y
			/ CUBES_SIZE][(int)ply->pos_x / CUBES_SIZE] == '1')
	{
		ply->pos_x = prev_pos_x;
		ply->pos_y = prev_pos_y;
	}
}

/* update pos (x, y ) of the player when WASD key are pressed */

static void	update_coord(t_game *game, t_player *ply)
{
	if (game->keys[0] == true)
	{
		ply->pos_x += cos(ply->ang_y * M_PI / 180) * 3;
		ply->pos_y -= sin(ply->ang_y * M_PI / 180) * 3;
	}
	if (game->keys[1] == true)
	{
		ply->pos_x -= cos(ply->ang_y * M_PI / 180) * 3;
		ply->pos_y += sin(ply->ang_y * M_PI / 180) * 3;
	}
	if (game->keys[2] == true)
	{
		ply->pos_x += cos((ply->ang_y + 90) * M_PI / 180) * 3;
		ply->pos_y -= sin((ply->ang_y + 90) * M_PI / 180) * 3;
	}
	if (game->keys[3] == true)
	{
		ply->pos_x += cos((ply->ang_y - 90) * M_PI / 180) * 3;
		ply->pos_y -= sin((ply->ang_y - 90) * M_PI / 180) * 3;
	}
}

/* update_player_data is used to modify the player data
(position and angle), when the WASD and directional arrows 
are pressed */

int	update_player_data(t_game *game, t_player *ply)
{
	double			prev_pos_x;
	double			prev_pos_y;
	double			prev_ang;

	prev_pos_x = ply->pos_x;
	prev_pos_y = ply->pos_y;
	prev_ang = ply->ang_y;
	update_coord(game, ply);
	if (game->keys[4])
		ply->ang_y -= 2;
	if (game->keys[5])
		ply->ang_y += 2;
	correct_pos(game, ply, prev_pos_x, prev_pos_y);
	return (is_data_updated(ply, prev_pos_x, prev_pos_y, prev_ang));
}
