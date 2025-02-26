/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:22:04 by erico-ke          #+#    #+#             */
/*   Updated: 2025/02/26 15:03:08 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	self_map_read(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'C')
				map->coin += 1;
			else if (map->map[i][j] == 'P')
			{
				map->player_c += 1;
				map->player.y = i;
				map->player.x = j;
			}
			else if (map->map[i][j] == 'E')
				map->exit_c += 1;
			else if (map->map[i][j] != '0' && map->map[i][j] != '1')
				map->null_check++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	set_map_dimensions(t_map *map)
{
	int		i;
	size_t	j;

	i = 0;
	j = ft_strlen(map->map[0]);
	while (map->map[i++] != NULL)
		if (map->map[i] && ft_strlen(map->map[i]) != j)
			map->null_check++;
	map->height = i - 1;
	map->width = j;
}

void	map_list_init(t_map *map)
{
	map->exit = 0;
	map->exit_c = 0;
	map->moves = 0;
	map->coin = 0;
	map->coin_c = 0;
	map->null_check = 0;
	map->player_c = 0;
	set_map_dimensions(map);
}
