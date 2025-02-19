/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:19:44 by erico-ke          #+#    #+#             */
/*   Updated: 2025/02/19 18:04:04 by erico-ke         ###   ########.fr       */
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
		mlx_image_to_window(map->wind, map->img.wall_i, x * IMG_PXL, y * IMG_PXL);
	else if (map->map[y][x] == '0')
		mlx_image_to_window(map->wind, map->img.tile_i, x * IMG_PXL, y * IMG_PXL);
	else if (map->map[y][x] == 'C')
		mlx_image_to_window(map->wind, map->img.collect_i, x * IMG_PXL, y * IMG_PXL);
	else if (map->map[y][x] == 'P')
		mlx_image_to_window(map->wind, map->img.player_i, x * IMG_PXL, y * IMG_PXL);
	else
	{
		if (map->coin_c != 0)
			mlx_image_to_window(map->wind, map->img.exit_c_i, x * IMG_PXL, y * IMG_PXL);
		else
			mlx_image_to_window(map->wind, map->img.exit_o_i, x * IMG_PXL, y * IMG_PXL);
	}
	if (map->map[y][x + 1])
		map_texture_charge(map, y , x + 1);
	else if (map->map[y + 1])
	{
		x = 0;
		map_texture_charge(map, y + 1, x);
	}
}

//PROBLEMA: como cargo imagenes arriba de imagenes empieza a ir lento el programa en algun momento, upsis.
//Buscar forma de borrar las img antiguas en el proceso

void	move_player_y(t_map *map, int y, int x, char dir)
{
	if (dir == 'w' && map->map[y - 1][x] != '1')
	{
		if (map->map[y - 1][x] == 'C')
			map->coin_c -= 1;
		if (map->map[y - 1][x] == 'E' && map->coin_c == 0)
		{
			mlx_close_window(map->wind);
			return ;
		}
		map->player.y -= 1;
		map->map[y - 1][x] = 'P';
		map->map[y][x] = '0';
		map_texture_charge(map, 0, 0);
	}
	else if (dir == 's' && map->map[y + 1][x] != '1')
	{
		if (map->map[y + 1][x] == 'C')
			map->coin_c -= 1;
		map->player.y += 1;
		map->map[y + 1][x] = 'P';
		map->map[y][x] = '0';
		map_texture_charge(map, 0, 0);
	}
}

void	move_player_x(t_map *map, int y, int x, char dir)
{
	if (dir == 'a' && map->map[y][x - 1] != '1')
	{
		if (map->map[y][x - 1] == 'C')
			map->coin_c -= 1;
		map->player.x -= 1;
		map->map[y][x - 1] = 'P';
		map->map[y][x] = '0';
		map_texture_charge(map, 0, 0);
	}
	else if (dir == 'd' && map->map[y][x + 1] != '1')
	{
		if (map->map[y][x + 1] == 'C')
			map->coin_c -= 1;
		map->player.x += 1;
		map->map[y][x + 1] = 'P';
		map->map[y][x] = '0';
		map_texture_charge(map, 0, 0);
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
	map->wind = mlx_init(IMG_PXL * map->map_width, IMG_PXL * (map->map_height), "so_long", false);
	image_init(map);
	map_texture_charge(map, 0, 0);
	mlx_key_hook(map->wind, &on_key_press , map);
	mlx_loop(map->wind);
	return (0);
}
int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		return (print_error("Please insert one argument, just one."));
	map = ft_calloc(1, sizeof(t_map));
	if (map_control(map, argv[1]) == EXIT_FAILURE)
	{
		free_all(map);
		return (EXIT_FAILURE);
	}
	init_window(map);
	free_all(map);
	mlx_delete_image(map->wind, map->img.collect_i);
	mlx_delete_image(map->wind, map->img.wall_i);
	mlx_delete_image(map->wind, map->img.exit_c_i);
	mlx_delete_image(map->wind, map->img.exit_o_i);
	mlx_delete_image(map->wind, map->img.player_i);
	mlx_delete_image(map->wind, map->img.tile_i);
	mlx_terminate(map->wind);
	return (EXIT_SUCCESS);
}

//Checkear por 0 o otros caracteres en las paredes, rodeados por paredes

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