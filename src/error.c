/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:55:14 by erico-ke          #+#    #+#             */
/*   Updated: 2025/03/03 12:04:54 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_error(char *ret)
{
	ft_printf("%s\n", 2, ret);
	return (EXIT_FAILURE);
}

void	the_freer(char	**free_me)
{
	int	i;

	i = 0;
	while (free_me[i])
	{
		free(free_me[i]);
		i++;
	}
	free(free_me);
	free_me = NULL;
}

void	free_all(t_map *map)
{
	if (map->map)
		the_freer(map->map);
	if (map->map_save)
		the_freer(map->map_save);
	free(map);
}

int	does_textures_exist(t_map *m)
{
	if (!m->img.coll || !m->img.wall || !m->img.exit_c || !m->img.exit_o
		|| !m->img.p || !m->img.tile)
		return (print_error("Error:\n	Textures file opening failed."));
	return (EXIT_SUCCESS);
}

void	textures_deleter(t_map *map)
{
	if (map->img.coll)
		mlx_delete_texture(map->img.coll);
	if (map->img.wall)
		mlx_delete_texture(map->img.wall);
	if (map->img.exit_c)
		mlx_delete_texture(map->img.exit_c);
	if (map->img.exit_o)
		mlx_delete_texture(map->img.exit_o);
	if (map->img.p)
		mlx_delete_texture(map->img.p);
	if (map->img.tile)
		mlx_delete_texture(map->img.tile);
}
