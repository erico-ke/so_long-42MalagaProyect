/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:16:31 by erico-ke          #+#    #+#             */
/*   Updated: 2025/03/03 16:55:12 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_p_y(t_map *map, int y, int x, char dir)
{
	if (dir == 'w' && map->map[y - 1][x] != '1')
	{
		if (map->map[y - 1][x] == 'C')
			map->coin_c -= 1;
		if (map->map[y - 1][x] == 'E' && map->coin_c == 0)
			mlx_close_window(map->wind);
		a_move_map_charge(map, y - 1, x);
		map->p.y -= 1;
	}
	else if (dir == 's' && map->map[y + 1][x] != '1')
	{
		if (map->map[y + 1][x] == 'C')
			map->coin_c -= 1;
		if (map->map[y + 1][x] == 'E' && map->coin_c == 0)
			mlx_close_window(map->wind);
		a_move_map_charge(map, y + 1, x);
		map->p.y += 1;
	}
}

static void	move_p_x(t_map *map, int y, int x, char dir)
{
	if (dir == 'a' && map->map[y][x - 1] != '1')
	{
		if (map->map[y][x - 1] == 'C')
			map->coin_c -= 1;
		if (map->map[y][x - 1] == 'E' && map->coin_c == 0)
			mlx_close_window(map->wind);
		a_move_map_charge(map, y, x - 1);
		map->p.x -= 1;
	}
	else if (dir == 'd' && map->map[y][x + 1] != '1')
	{
		if (map->map[y][x + 1] == 'C')
			map->coin_c -= 1;
		if (map->map[y][x + 1] == 'E' && map->coin_c == 0)
			mlx_close_window(map->wind);
		a_move_map_charge(map, y, x + 1);
		map->p.x += 1;
	}
}

void	on_key_press(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	/* int i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	} */
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->wind);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_p_y(map, map->p.y, map->p.x, 'w');
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_p_y(map, map->p.y, map->p.x, 's');
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_p_x(map, map->p.y, map->p.x, 'a');
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_p_x(map, map->p.y, map->p.x, 'd');
}
