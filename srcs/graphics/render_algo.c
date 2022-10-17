/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeharpr <mpeharpr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:47:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/17 03:14:03 by mpeharpr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Render walls from the map with the raycasting algorithm */
void    render_walls(t_game *game, int img_index)
{
    t_player    *ply;
    double      start_ang;
    double      wall_height;
    double      wall_y;
    int         y;
    int         x;
    t_raysult   res;

    ply = game->player;
    start_ang = ply->ang_y - (PLY_VIEW_FOV_DEG / 2);
    x = 0;
    while (start_ang < ply->ang_y + (PLY_VIEW_FOV_DEG / 2))
    {
        send_raycast(game, start_ang, &res);
        wall_height = ply->dist_from_proj * CUBES_SIZE / res.dist;
        wall_y = (game->wdw_y / 2) - (wall_height / 2);

        y = wall_y;
        if (y < 0)
            y = 0;
        while (y < game->imgs_set[img_index]->height && y < wall_y + wall_height)
        {
            mlx_pixel_put_to_img(game->imgs_set[img_index], x, y, 0x00e67e22);
            y++;
        }

        x++;
        start_ang += (double)PLY_VIEW_FOV_DEG / (double)game->wdw_x;
    }
}
