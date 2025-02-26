/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:19:44 by erico-ke          #+#    #+#             */
/*   Updated: 2025/02/26 16:37:41 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void image_init(t_map *map)
{
	map->img.collectible = mlx_load_png("./textures/Egg_item.png");
	map->img.wall = mlx_load_png("./textures/Water.png");
	map->img.exit_c = mlx_load_png("./textures/GoldMine_Inactive.png");
	map->img.exit_o = mlx_load_png("./textures/GoldMine_Active.png");
	map->img.player = mlx_load_png("./textures/Dino.png");
	map->img.tile = mlx_load_png("./textures/floor.png");
	map->img.collect_i = mlx_texture_to_image(map->wind, map->img.collectible);
	map->img.wall_i = mlx_texture_to_image(map->wind, map->img.wall);
	map->img.exit_c_i = mlx_texture_to_image(map->wind, map->img.exit_c);
	map->img.exit_o_i = mlx_texture_to_image(map->wind, map->img.exit_o);
	map->img.player_i = mlx_texture_to_image(map->wind, map->img.player);
	map->img.tile_i = mlx_texture_to_image(map->wind, map->img.tile);
	mlx_delete_texture(map->img.collectible);
	mlx_delete_texture(map->img.wall);
	mlx_delete_texture(map->img.exit_c);
	mlx_delete_texture(map->img.exit_o);
	mlx_delete_texture(map->img.player);
	mlx_delete_texture(map->img.tile);
}

void	map_texture_charge(t_map *map, int y, int x)
{
	if (map->map[y][x] == '1')
		mlx_image_to_window(map->wind, map->img.wall_i, x * IPXL, y * IPXL);
	else if (map->map[y][x] == '0')
		mlx_image_to_window(map->wind, map->img.tile_i, x * IPXL, y * IPXL);
	else if (map->map[y][x] == 'C')
		mlx_image_to_window(map->wind, map->img.collect_i, x * IPXL, y * IPXL);
	else if (map->map[y][x] == 'P')
		mlx_image_to_window(map->wind, map->img.player_i, x * IPXL, y * IPXL);
	else
	{
		if (map->coin_c != 0)
			mlx_image_to_window(map->wind, map->img.exit_c_i, x * IPXL,
				y * IPXL);
		else
			mlx_image_to_window(map->wind, map->img.exit_o_i, x * IPXL,
				y * IPXL);
	}
	if (map->map[y][x + 1])
		map_texture_charge(map, y , x + 1);
	else if (map->map[y + 1])
	{
		x = 0;
		map_texture_charge(map, y + 1, x);
	}
}

void	a_move_map_charge(t_map *map, int ye, int xe)
{
	mlx_image_to_window(map->wind, map->img.tile_i, map->player.x * IPXL, map->player.y * IPXL);
	mlx_image_to_window(map->wind, map->img.player_i, xe * IPXL, ye * IPXL);
	map->moves++;
	ft_printf("Movements made: %d\n", 1, map->moves);
}

void	move_player_y(t_map *map, int y, int x, char dir)
{
	if (dir == 'w' && map->map[y - 1][x] != '1')
	{
		if (map->map[y - 1][x] == 'C')
			map->coin_c -= 1;
		if (map->map[y - 1][x] == 'E' && map->coin_c == 0)
			mlx_close_window(map->wind);
		map->player.y -= 1;
		map->map[y - 1][x] = 'P';
		map->map[y][x] = '0';
		a_move_map_charge(map, y - 1, x);
	}
	else if (dir == 's' && map->map[y + 1][x] != '1')
	{
		if (map->map[y + 1][x] == 'C')
			map->coin_c -= 1;
		if (map->map[y + 1][x] == 'E' && map->coin_c == 0)
			mlx_close_window(map->wind);
		map->player.y += 1;
		map->map[y + 1][x] = 'P';
		map->map[y][x] = '0';
		a_move_map_charge(map, y + 1, x);
	}
}

void	move_player_x(t_map *map, int y, int x, char dir)
{
	if (dir == 'a' && map->map[y][x - 1] != '1')
	{
		if (map->map[y][x - 1] == 'C')
			map->coin_c -= 1;
		if (map->map[y][x - 1] == 'E' && map->coin_c == 0)
			mlx_close_window(map->wind);
		map->player.x -= 1;
		map->map[y][x - 1] = 'P';
		map->map[y][x] = '0';
		a_move_map_charge(map, y, x - 1);
	}
	else if (dir == 'd' && map->map[y][x + 1] != '1')
	{
		if (map->map[y][x + 1] == 'C')
			map->coin_c -= 1;
		if (map->map[y][x + 1] == 'E' && map->coin_c == 0)
			mlx_close_window(map->wind);
		map->player.x += 1;
		map->map[y][x + 1] = 'P';
		map->map[y][x] = '0';
		a_move_map_charge(map, y, x + 1);
	}
}

void	on_key_press(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->wind);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move_player_y(map, map->player.y, map->player.x, 'w');
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move_player_y(map, map->player.y, map->player.x, 's');
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move_player_x(map, map->player.y, map->player.x, 'a');
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move_player_x(map, map->player.y, map->player.x, 'd');
}

int	init_window(t_map *map)
{
	map->wind = mlx_init(IPXL * map->width, IPXL * map->height, "so_long", 0);
	image_init(map);
	map_texture_charge(map, 0, 0);
	mlx_key_hook(map->wind, &on_key_press , map);
	mlx_loop(map->wind);
	return (0);
}

void	map_img_ter(t_map *map)
{
	mlx_delete_image(map->wind, map->img.collect_i);
	mlx_delete_image(map->wind, map->img.wall_i);
	mlx_delete_image(map->wind, map->img.exit_c_i);
	mlx_delete_image(map->wind, map->img.exit_o_i);
	mlx_delete_image(map->wind, map->img.player_i);
	mlx_delete_image(map->wind, map->img.tile_i);
	mlx_terminate(map->wind);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		return (print_error("Please insert one argument, just one."));
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (print_error("Malloc failed."));
	if (map_control(map, argv[1]) == EXIT_FAILURE)
	{
		free_all(map);
		return (EXIT_FAILURE);
	}
	init_window(map);
	map_img_ter(map);
	free_all(map);
	return (EXIT_SUCCESS);
}

/* 
COSAS A AGREGAR:
checkeo de que existan las texturas
acortar lineas muy largas
que el player no se coma la salida...
*/

/* 
mlx_init para inicializar la ventana
mlx_set_window_size para inicializar con tamaño variable en caso de ser necesario
mlx_loop para que empiece el renderizado del loop(abre ventana)
mlx_close_window para cerrar la ventana
mlx_terminate limpia todo lo de la ventana
mlx_set_icon, le da un icono a la ventana en la barra de apps(abajo)
mlx_is_key_down, checkea si una key esta apretada
mlx_load_xpm42 carga de texturas en formato xpm42
mlx_delete_xpm42 libera la data de la textura, destruyendola
mlx_key_hook para detectar teclas presionadas durante el loop
 */