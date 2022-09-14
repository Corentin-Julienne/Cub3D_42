/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:03:18 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/14 17:43:25 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* check_invalid_nl verify that the map does not contain any empty line,
which is not allowed by the instructions PDF */

static void	check_invalid_nl(t_map_data *map_data)
{
	char			**map_lines;
	int				i;

	map_lines = map_data->lines;
	i = 0;
	while (map_lines && map_lines[i])
	{
		if (map_lines[i] == '\n' && map_lines[i + 1] 
			&& map_lines[i + 1] == '\n')
			; // handle with error msg
		i++;
	}
	free(map_data->lines);
	map_data->lines = NULL;
}

static void	check_invalid_char(t_map_data *map_data)
{
	int		x;
	int		y;

	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			if (!ft_isspace(map_data->map[y][x])
				&& !ft_strchr(map_data->map[y][x], "01NSEW"))
				; // handle error (invalid character)
			x++;
		}
		y++;
	}
}

/* when verifying that a 0 is not actually close to a free space,
check wether the direction checked is in the map or not,
in order to avoid segfaults */

static int	is_out_of_map(t_map_data *map_data, int x, int y)
{
	int		size_line;
	
	size_line = ft_strlen(map_data->map[y]);
	if (y < 0 || y >= map_data->size_y)
		return (1);
	if (x < 0 || x >= size_line)
		return (1);
	return (0);
}

static int	is_pos_valid(t_map_data *map_data, int x, int y)
{
	if (is_out_of_map(map_data, x + 1, y) || ft_isspace(map_data->map[y][x + 1]))
		return (0);
	else if (is_out_of_map(map_data, x - 1, y) || ft_isspace(map_data->map[y][x - 1]))
		return (0);
	else if (is_out_of_map(map_data, x, y + 1) || ft_isspace(map_data->map[y + 1][x]))
		return (0);
	else if (is_out_of_map(map_data, x, y - 1) || ft_isspace(map_data->map[y - 1][x]))
		return (0);
	return (1);
}

void	check_map_validity(t_map_data *map_data)
{
	int			x;
	int			y;
	
	check_invalid_nl(map_data);
	check_invalid_char(map_data);
	x = 0;
	y = 0;
	while (map_data->map[y])
	{
		x = 0;
		while (map_data->map[y][x])
		{
			if (ft_strchr("0NSEW", map_data->map[y][x]))
			{
				if (!is_pos_valid(map_data, x, y))
					; // handle error : unvalid map 				
			}
			x++;
		}
		y++;
	}
}