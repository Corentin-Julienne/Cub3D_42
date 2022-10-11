/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:47:08 by cjulienn          #+#    #+#             */
/*   Updated: 2022/10/10 17:07:41 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Render walls from the map with the raycasting algorithm */
void    render_walls(t_game *game, int img_index)
{
    t_player    *ply;
    t_raycast   ray;
    double      wall_height;
    double      dist_wall;
    double      top_wall_y;
	int		    y;

    ply = game->player;
    for (int i = 0; i < game->wdw_x; i++) // replace by a while loop
    {
        raycast(game, &ray, ((double)i * ((double)PLY_VIEW_FOV_DEG / (double)game->wdw_x)));
        dist_wall = calc_dist(ply->pos_x, ply->pos_y, ray.wall_touch_x, ray.wall_touch_y);
        wall_height = (CUBES_SIZE / dist_wall) * ply->dist_from_proj;
        top_wall_y = (game->wdw_y / 2) - (wall_height / 2);
    
    	y = top_wall_y;
        while (y < game->imgs_set[img_index]->height && y < top_wall_y + wall_height)
        {
            mlx_pixel_put_to_img(game->imgs_set[img_index], i, y, 0x00FFFF00);
            y++;
        }
    }
}
