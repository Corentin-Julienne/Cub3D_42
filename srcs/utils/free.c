/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:13:25 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/14 17:42:09 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_and_nullify(void **to_free) // to test
{
	if (to_free)
	{
		free(*to_free);
		*to_free = NULL;	
	}
}

/* free the struct in order to avoid leaks
use when normal program termination or when there is an error */

void	free_map_data(t_map_data *map_data)
{
	free_and_nullify(&map_data->lines);
	if (map_data->cub)
		free_split(map_data->cub);
	if (map_data->map)
		free_split(map_data->map);
	free_and_nullify(map_data->no_text);
	free_and_nullify(map_data->so_text);
	free_and_nullify(map_data->ea_text);
	free_and_nullify(map_data->we_text);
	free_and_nullify(map_data->floor_col);
	free_and_nullify(map_data->ceil_col);
	free(map_data);
	map_data = NULL;
}

/* in case of a probleme of alloc during the split,
use that func to free every malloqued str in the array,
then the array itself */

void	free_problem_str_arr(char **split, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(split[j]);
		split[j] = NULL;
		j++;
	}
	free(split);
	split = NULL;
}

/* free the product of a ft_split. Free every string in the array,
and then the array itself */

void	free_split(char **split)
{
	size_t		i;

	i = 0;
	while(split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}