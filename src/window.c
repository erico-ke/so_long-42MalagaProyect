/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:53:11 by erico-ke          #+#    #+#             */
/*   Updated: 2025/02/27 14:29:40 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	image_init(t_map *map)
{
	map->img.coll = mlx_load_png("./textures/Egg_item.png");
	map->img.wall = mlx_load_png("./textures/Water.png");
	map->img.exit_c = mlx_load_png("./textures/GoldMine_Inactive.png");
	map->img.exit_o = mlx_load_png("./textures/GoldMine_Active.png");
	map->img.p = mlx_load_png("./textures/Dino.png");
	map->img.tile = mlx_load_png("./textures/floor.png");
	if (does_textures_exist(map) == EXIT_SUCCESS)
	{
		map->img.collect_i = mlx_texture_to_image(map->wind, map->img.coll);
		map->img.wall_i = mlx_texture_to_image(map->wind, map->img.wall);
		map->img.exit_c_i = mlx_texture_to_image(map->wind, map->img.exit_c);
		map->img.exit_o_i = mlx_texture_to_image(map->wind, map->img.exit_o);
		map->img.p_i = mlx_texture_to_image(map->wind, map->img.p);
		map->img.ti_i = mlx_texture_to_image(map->wind, map->img.tile);
		textures_deleter(map);
		return (EXIT_SUCCESS);
	}
	textures_deleter(map);
	return (EXIT_FAILURE);
}

void	map_texture_charge(t_map *map, int y, int x)
{
	if (map->map[y][x] == '1')
		mlx_image_to_window(map->wind, map->img.wall_i, x * PXL, y * PXL);
	else if (map->map[y][x] == '0')
		mlx_image_to_window(map->wind, map->img.ti_i, x * PXL, y * PXL);
	else if (map->map[y][x] == 'C')
		mlx_image_to_window(map->wind, map->img.collect_i, x * PXL, y * PXL);
	else if (map->map[y][x] == 'P')
		mlx_image_to_window(map->wind, map->img.p_i, x * PXL, y * PXL);
	else
	{
		mlx_image_to_window(map->wind, map->img.exit_c_i, x * PXL, y * PXL);
		map->exity = y;
		map->exitx = x;
	}
	if (map->map[y][x + 1])
		map_texture_charge(map, y, x + 1);
	else if (map->map[y + 1])
	{
		x = 0;
		map_texture_charge(map, y + 1, x);
	}
}

void	a_move_map_charge(t_map *m, int ye, int xe)
{
	if (m->coin_c == 0)
		mlx_image_to_window(m->wind, m->img.exit_o_i, m->p.x * PXL,
			m->p.y * PXL);
	if (m->p.x == m->exitx && m->p.y == m->exity)
	{
		mlx_image_to_window(m->wind, m->img.exit_c_i, m->p.x * PXL,
			m->p.y * PXL);
		m->map[m->exitx][m->exity] = 'E';
	}
	else
		mlx_image_to_window(m->wind, m->img.ti_i, m->p.x * PXL, m->p.y * PXL);
	mlx_image_to_window(m->wind, m->img.p_i, xe * PXL, ye * PXL);
	m->moves++;
	ft_printf("Movements made: %d\n", 1, m->moves);
}

int	init_window(t_map *map)
{
	map->wind = mlx_init(PXL * map->width, PXL * map->height, "so_long", 0);
	if (image_init(map) == EXIT_SUCCESS)
	{
		map_texture_charge(map, 0, 0);
		mlx_key_hook(map->wind, &on_key_press, map);
		mlx_loop(map->wind);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

void	map_img_ter(t_map *map)
{
	mlx_delete_image(map->wind, map->img.collect_i);
	mlx_delete_image(map->wind, map->img.wall_i);
	mlx_delete_image(map->wind, map->img.exit_c_i);
	mlx_delete_image(map->wind, map->img.exit_o_i);
	mlx_delete_image(map->wind, map->img.p_i);
	mlx_delete_image(map->wind, map->img.ti_i);
	mlx_terminate(map->wind);
}
